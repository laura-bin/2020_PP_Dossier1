/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database alphanumeric indexes creation
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "db_file/catalog.h"
#include "db_file/alpha_index.h"
#include "utils/string_comparison.h"

/* PRIVATE FUNCTIONS */

/**
 * Compares two alphanumeric indexes (case insensitive)
 * 
 * @param index1: first index to compare
 * @param index2: second index to compare
 * 
 * @return either
 *      < 0 if the first index value is before the second in alphabetical order
 *      0 if the two values are identical
 *      > 0 if the first index value is after the second in alphabetical order
 */
int compare_alpha_index(const void *index1, const void *index2) {
    struct alpha_entity *i1 = (struct alpha_entity *) index1;
    struct alpha_entity *i2 = (struct alpha_entity *) index2;

    char *i1_value = lower_str(i1->value);
    char *i2_value = lower_str(i2->value);

    int res = strcmp(i1_value, i2_value);

    free(i1_value);
    free(i2_value);

    return res;
}

/**
 * Creates the binary tree for an alphanumeric index
 * 
 * @param db: database information stored in RAM
 * @param type: index type
 * @param head: tree or subtree head
 * @param size: tree size
 * 
 * @return the offset of the head node
 */
unsigned create_binary_tree(struct db *db, enum alpha_index type, unsigned head, int size) {
    int left_size;
    int right_size;
    unsigned offset, head_left, head_right;
    struct alpha_entity index;

    left_size = (size - 1) / 2;
    right_size = size - 1 - left_size;

    head_left = head - left_size + (left_size - 1) / 2;
    head_right = head + (right_size - 1) / 2 + 1;

    offset = db->header.offset_alpha_index[PERS_BY_LASTNAME] + head*sizeof(struct alpha_entity);
    fseek(db->dat_file, offset, SEEK_SET);
    fread(&index, 1, sizeof(struct alpha_entity), db->dat_file);

    if (left_size > 0) {
        index.left = create_binary_tree(db, type, head_left, left_size);
    } else {
        index.left = UINT_MAX;
    }

    if (right_size > 0) {
        index.rigth = create_binary_tree(db, type, head_right, right_size);
    } else {
        index.rigth = UINT_MAX;
    }

    fseek(db->dat_file, offset, SEEK_SET);
    fwrite(&index, 1, sizeof(struct alpha_entity), db->dat_file);

    return offset;
}

/* HEADER IMPLEMENTATION */

int create_person_by_lastname(struct db *db) {
    struct person person;
    struct alpha_entity *index;
    const char *index_type;
    unsigned offset;
    unsigned i;

    // init variables
    index_type = alpha_indexes_metadata[PERS_BY_LASTNAME].prefix;
    offset = db->header.offset_table[PERSON];
    index = malloc(db->header.n_rec_table[PERSON] * sizeof(struct alpha_entity));
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
        strncpy(index[i].value, person.lastname, PERSON_LASTNAME_LEN);
        strcpy(index[i].type, index_type);

        offset += sizeof(struct person);
    }

    // sort the list
    qsort(index, db->header.n_rec_table[PERSON], sizeof(struct alpha_entity),
            &compare_alpha_index);

    // write the sorted list in the database file
    fseek(db->dat_file, db->header.offset_alpha_index[PERS_BY_LASTNAME], SEEK_SET);
    for (i = 0; i < db->header.n_rec_table[PERSON]; i++) {
        fwrite(&index[i], sizeof(struct alpha_entity), 1, db->dat_file);
    }

    // create the binary tree (fill left & right offsets)
    db->header.offset_tree[PERS_BY_LASTNAME] = create_binary_tree(db, PERS_BY_LASTNAME,
            (db->header.n_rec_table[PERSON]-1) / 2, db->header.n_rec_table[PERSON]);

    // write the updated header in the database file
    fseek(db->dat_file, 0, SEEK_SET);
    if (fwrite(&db->header, sizeof(db->header), 1, db->dat_file) != 1) {
        return -1;
    }

    free(index);
    return 0;
}
