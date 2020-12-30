/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database numeric indexes creation
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "db_file/catalog.h"
#include "db_file/num_index.h"

/**
 * Compares two numeric indexes
 * 
 * @param index1: first index to compare
 * @param index2: second index to compare
 * 
 * @return either
 *      < 0 if the first index value is lower than the second
 *      0 if the two values are equals
 *      > 0 if the first index value is higher than the second
 */
int compare_num_index(const void *index1, const void *index2) {
    struct num_entity *i1 = (struct num_entity *) index1;
    struct num_entity *i2 = (struct num_entity *) index2;

    return i1->value - i2->value;
}

/* HEADER IMPLEMENTATION */

int create_person_by_company_id(struct db *db) {
    struct person person;
    struct num_entity *index;
    const char *index_type;
    unsigned offset;
    unsigned i;

    // init variables
    index_type = num_indexes_metadata[PERS_BY_COMP_ID].prefix;
    offset = db->header.offset_table[PERSON];
    index = malloc(db->header.n_rec_table[PERSON] * sizeof(struct num_entity));
    if (index == NULL) {
        return -1;
    }

    fseek(db->dat_file, offset, SEEK_SET);
    for (i = 0; i < db->header.n_rec_table[PERSON]; i++) {
        // load person
        memset(&person, 0, sizeof(struct person));
        if (fread(&person, sizeof(struct person), 1, db->dat_file) != 1) {
            free(index);
            return -1;
        }

        // fill the index
        index[i].offset = offset;
        index[i].value = person.id_company;
        strcpy(index[i].type, index_type);

        offset += sizeof(struct person);
    }

    // sort the list
    qsort(index, db->header.n_rec_table[PERSON], sizeof(struct num_entity),
            &compare_num_index);

    // write the sorted list in the database file
    fseek(db->dat_file, db->header.offset_num_index[PERS_BY_COMP_ID], SEEK_SET);
    for (i = 0; i < db->header.n_rec_table[PERSON]; i++) {
        fwrite(&index[i], sizeof(struct num_entity), 1, db->dat_file);
    }

    free(index);
    return 0;
}
