/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database header creation
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <errno.h>
#include <string.h>

#include "db_file/catalog.h"
#include "db_file/header.h"
#include "utils/logger.h"

/* PRIVATE FUNCTIONS */

/**
 * Fills the tables information
 * 
 * @param db: database information stored in RAM
 * @param offset: first offset available
 */
void fill_tables_info(struct db *db, size_t *offset) {
    enum table i;

    for (i = 0; i < TAB_COUNT; i++) {
        const struct table_metadata *table = &tables_metadata[i];

        db->header.n_res_table[i] = table->n_reserved;
        db->header.offset_table[i] = *offset;
        db->header.n_rec_table[i] = 0;

        *offset += table->n_reserved * table->size;
    }
}

/**
 * Fills the numeric indexes information
 * 
 * @param db: database information stored in RAM
 * @param offset: first offset available
 */
void fill_num_indexes_info(struct db *db, size_t *offset) {
    enum num_index i;

    for (i = 0; i < NUM_INDEX_COUNT; i++) {
        const struct index_metadata *index = &num_indexes_metadata[i];

        db->header.n_res_num_index[i] = index->n_reserved;
        db->header.offset_num_index[i] = *offset;

        *offset += index->n_reserved * index->size;
    }
}

/**
 * Fills the alphanumeric indexes information
 * 
 * @param db: database information stored in RAM
 * @param offset: first offset available
 */
void fill_alpha_indexes_info(struct db *db, size_t *offset) {
    enum alpha_index i;

    for (i = 0; i < ALPHA_INDEX_COUNT; i++) {
        const struct index_metadata *index = &alpha_indexes_metadata[i];

        db->header.n_res_alpha_index[i] = index->n_reserved;
        db->header.offset_alpha_index[i] = *offset;

        *offset += index->n_reserved * index->size;
    }
}

/* HEADER IMPLEMENTATION */

int create_header(struct db *db) {
    size_t offset;

    memset(&db->header, 0, sizeof(struct header));
    strcpy(db->header.db_name, "db_clients");
    offset = sizeof(struct header);

    fill_tables_info(db, &offset);
    fill_num_indexes_info(db, &offset);
    fill_alpha_indexes_info(db, &offset);

    db->header.size = offset;

    if (fwrite(&db->header, sizeof(db->header), 1, db->dat_file) != 1) {
        return -1;
    }

    return 0;
}
