/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Generic sequential search
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <ctype.h>
#include <string.h>

#include "search/sequential_search.h"
#include "db_file/database.h"

struct search_result sequential_search(struct db *db, enum table tab, char *searched) {
    unsigned i;                     // record index
    void *found;                    // record found

    // results initialization
    struct search_result res = {
        .result_count = 0,
        .head = NULL,
        .tail = NULL,
    };

    const struct table_metadata *table = &tables_metadata[tab];
    
    for (i = 0; i < db->header.n_rec_table[tab]; i++) {
        found = (*table->compare)(db, i, searched);
        if (found != NULL) {
            res.tail = append_item(res.tail, found);
            if (res.head == NULL) res.head = res.tail;
            res.result_count++;
        }
    }

    return res;
}
