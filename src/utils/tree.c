#include "db_file/database.h"

// algorithme de creation d'un arbre
// retourne toujours la tête de l'arbre 
unsigned tree_ipn(struct db *db, unsigned head, int head_size) {
    int left_size;
    int right_size;
    unsigned offset, head_left, head_right;
    struct person_by_lastname index;

    left_size = (head_size - 1) / 2;
    right_size = head_size - 1 - left_size;

    head_left = head - left_size + (left_size - 1) / 2;
    head_right = head + (right_size - 1) / 2 + 1;

    offset = db->header.index_off[PERS_BY_LASTNAME] + head*sizeof(struct person_by_lastname);
    fseek(db->dat_file, offset, SEEK_SET);
    fread(&index, 1, sizeof(struct person_by_lastname), db->dat_file);

    if (left_size > 0) {
        index.left = tree_ipn(db, head_left, left_size);
    }

    if (right_size > 0) {
        index.rigth = tree_ipn(db, head_right, right_size);
    }

    fseek(db->dat_file, cur_off, SEEK_SET);
    fread(&index, 1, sizeof(struct person_by_lastname), db->dat_file);

    return offset;
}