/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database header creation
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <string.h>

#include "db_file/catalog.h"
#include "db_file/header.h"

ssize_t create_header(struct db *db) {
    size_t offset;          // table or index offset
    size_t max_size = 0;    // max entity size
    enum table i_tab;       // table iteration index
    enum index i_index;     // index iteration index

    memset(&db->header, 0, sizeof(struct header));
    strcpy(db->header.db_name, "db_clients");
    offset = sizeof(struct header);

    for (i_tab = 0; i_tab < TAB_COUNT; i_tab++) {
        const struct table_metadata *table = &tables_metadata[i_tab];

        db->header.n_table_res[i_tab] = table->n_reserved;
        db->header.table_off[i_tab] = offset;
        db->header.n_table_rec[i_tab] = 0;

        offset += table->n_reserved * table->size;
        max_size = max_size > table->size ? max_size : table->size;
    }

    for (i_index = 0; i_index < INDEX_COUNT; i_index++) {
        const struct index_metadata *index = &indexes_metadata[i_index];

        db->header.n_index_res[i_index] = index->n_reserved;
        db->header.index_off[i_index] = offset;
        db->header.n_index_rec[i_index] = 0;

        max_size = max_size > index->size ? max_size : index->size;
    }

    db->header.size = offset;

    if (fwrite(&db->header, sizeof(db->header), 1, db->dat_file) != 1) {
        return -1;
    }

    return max_size;
}
