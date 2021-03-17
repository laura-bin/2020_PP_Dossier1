/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 * 
 * Utils:
 *  - get a tuple by id
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <errno.h>
#include <string.h>

#include "report/utils.h"
#include "search/binary_search.h"
#include "ui/ui-utils.h"
#include "utils/logger.h"

void *get_one_by_id(struct db *db, enum table table, unsigned *out_searched) {
    unsigned offset;    // tuple offset found
    void *tuple;        // tuple found

    const struct table_metadata *table_info = &tables_metadata[table];
    
    // get the user input
    if (!*out_searched) {
        printf("Enter the id searched: ");
        *out_searched = get_uns_input();
    }

    // get the tuple offset (or the offset of the nearest result)
    offset = binary_search(db, *out_searched, 0, db->header.n_rec_table[table]-1, table);
    if (offset == UINT_MAX) {
        log_info(db, "Searching tuple by id", strerror(errno));
        return NULL;
    }

    // get the tuple from the database file
    tuple = (*table_info->read)(db, offset);
    if (tuple == NULL) {
        log_info(db, "Reading tuple into the database file", strerror(errno));
    }

    return tuple;
}
