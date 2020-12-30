/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database file views:
 *  - print code tables from their buffers (country, job, industry, group)
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <ctype.h>
#include <string.h>

#include "db_file/database.h"
#include "search/sequential_search.h"
#include "table/country.h"
#include "table/job.h"
#include "table/industry.h"
#include "table/group.h"
#include "ui/ui-utils.h"
#include "utils/linked_list.h"

/* PRIVATE FUNCTION */

/**
 * Searches records in the RAM stored buffer (sequential search)
 * and shows the paginated list of results
 *
 * @param db: database information stored in RAM
 * @param tab: table enum
 */
int sequential_search(struct db *db, enum table tab) {
    char searched[MAX_LEN];         // substring searched
    unsigned i;                     // record index
    unsigned results = 0;           // number of records found
    struct node *head = NULL;       // linked list head
    struct node *cur_node = NULL;   // linked list current node
    void *found;                    // record found

    const struct table_metadata *table = &tables_metadata[tab];

    printf("Enter the substring searched: ");
    get_text_input(searched, MAX_LEN);

    for (i = 0; i < db->header.n_rec_table[tab]; i++) {
        found = (*table->compare)(db, i, searched);
        if (found != NULL) {
            cur_node = append_item(cur_node, found);
            if (head == NULL) head = cur_node;
            results++;
        }
    }

    paginate(results, head, table->print, table->print_header);
    free_list(head, 0);

    return 0;
}

/* HEADER IMPLEMENTATION */

int search_countries(struct db *db) {
    return sequential_search(db, COUNTRY);
}

int search_jobs(struct db *db) {
    return sequential_search(db, JOB);
}

int search_industries(struct db *db) {
    return sequential_search(db, INDUSTRY);
}

int search_groups(struct db *db) {
    return sequential_search(db, GROUP);
}
