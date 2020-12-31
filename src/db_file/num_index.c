/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database numeric indexes creation
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "db_file/catalog.h"
#include "db_file/num_index.h"
#include "utils/sort.h"

/* PRIVATE FUNCTION */

/**
 * Compares two numeric indexes
 * 
 * @param index1: first index to compare
 * @param index2: second index to compare
 * 
 * @return either
 *      < 0 if the first index value is lower than the second
 *      0 if the two values are equals
 *      > 0 if the first index value is greater than the second
 */
int compare_num_index(const void *index1, const void *index2) {
    struct num_entity *i1 = (struct num_entity *) index1;
    struct num_entity *i2 = (struct num_entity *) index2;

    return i1->value - i2->value;
}

/* HEADER IMPLEMENTATION */

int create_num_index(struct db *db, enum num_index index_type) {
    struct num_entity *index;
    unsigned offset;
    unsigned i;

    const struct num_index_metadata *index_info = &num_indexes_metadata[index_type];
    const struct table_metadata *table_info = &tables_metadata[index_info->table];

    // init variables
    offset = db->header.offset_table[index_info->table];
    index = malloc(db->header.n_rec_table[index_info->table] * sizeof(struct num_entity));
    if (index == NULL) {
        return -1;
    }

    // fill the index
    for (i = 0; i < db->header.n_rec_table[index_info->table]; i++) {
        strcpy(index[i].type, index_info->prefix);
        index[i].offset = offset;
        index[i].value = (*index_info->read_value)(db, offset);

        if (index[i].value == UINT_MAX) {
            free(index);
            return -1;
        }

        offset += table_info->size;
    }

    // sort the list
    // qsort(index, db->header.n_rec_table[index_info->table], sizeof(struct num_entity),
    //         &compare_num_index);
    quick_sort(index, db->header.n_rec_table[index_info->table], sizeof(struct num_entity),
            &compare_num_index);

    // write the sorted list in the database file
    fseek(db->dat_file, db->header.offset_num_index[index_type], SEEK_SET);
    for (i = 0; i < db->header.n_rec_table[index_info->table]; i++) {
        if (fwrite(&index[i], sizeof(struct num_entity), 1, db->dat_file) != 1) {
            free(index);
            return -1;
        }
    }

    free(index);
    return 0;
}
