/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database file views:
 *  - print code tables from their buffers (county, job, industry, group)
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <ctype.h>
#include <string.h>

#include "db_file/database.h"
#include "db_file/seq_search.h"
#include "table/country.h"
#include "table/job.h"
#include "table/industry.h"
#include "table/group.h"
#include "ui/ui-utils.h"
#include "utils/linked_list.h"

/* PRIVATE FUNCTION */

/**
 * Searches a record in the RAM stored buffer (sequential search)
 *
 * @param db: database information stored in RAM
 * @param tab: table enum
 * @param compare: comparison function
 * @param print: print record function
 * @param print_header: print table header (fields names) function
 */
int seq_search(struct db *db, enum table tab,
            void *(*compare)(struct db *, unsigned, char *),
            void (*print)(void *),
            void (*print_header)(void)) {
    char searched[64];              // string searched
    unsigned i;                     // record index
    unsigned results = 0;           // number of records found
    struct node *head = NULL;       // linked list head
    struct node *cur_node = NULL;   // linked list current node
    void *found;                    // record found

    printf("Enter the substring searched: ");
    get_text_input(searched, 64);

    for (i = 0; i < db->header.n_recorded[tab]; i++) {
        found = (*compare) (db, i, searched);
        if (found != NULL) {
            cur_node = append_item(cur_node, found);
            if (head == NULL) head = cur_node;
            results++;
        }
    }

    if (! results) {
        puts("No result found");
    } else {
        paginate(results, head, print, print_header);
        free_list(head);
    }

    return 0;
}

/* HEADER IMPLEMENTATION */

int search_countries(struct db *db) {
    return seq_search(db, COUNTRY, &compare_country,
        (void (*)(void *))&print_country,&print_country_header);
}

int search_jobs(struct db *db) {
    return seq_search(db, JOB, &compare_job,
        (void (*)(void *))&print_job, &print_job_header);
}

int search_industries(struct db *db) {
    return seq_search(db, INDUSTRY, &compare_industry,
        (void (*)(void *))&print_industry, &print_industry_header);
}

int search_groups(struct db *db) {
    return seq_search(db, GROUP, &compare_group,
        (void (*)(void *))&print_group, &print_group_header);
}
