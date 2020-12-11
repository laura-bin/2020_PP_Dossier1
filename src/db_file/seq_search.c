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
#include "ui/ui-utils.h"
#include "utils/linked_list.h"

// TODO pagination
// TODO print table header
// TODO check if table is empty

/* PRIVATE FUNCTION */

/**
 * Compares two strings: test if a given string begins by a given prefix
 *  - case insensitive
 *  - returns 1 if the prefix is empty
 *
 * @param str: string tested
 * @param prefix: string prefix tested
 *
 * @return either:
 *          1 if the string begins by the prefix
 *          0 if not
 */
int string_starts_with(char *str, char *prefix) {
    size_t str_len = strlen(str);
    size_t prefix_len = strlen(prefix);

    if (prefix_len <= str_len) {
        size_t i = 0;
        for (i = 0; i < prefix_len; i++) {
            if (tolower(str[i]) != tolower(prefix[i])) return 0;
        }
        return 1;
    }
    return 0;
}

/* HEADER IMPLEMENTATION */

int search_countries(struct db *db) {
    char searched[24];
    unsigned i;
    int results = 0;
    struct node *head = NULL;
    struct node *cur_node = NULL;

    printf("Enter the name searched: ");
    get_text_input(searched, 24);

    for (i = 0; i < db->header.n_recorded[COUNTRY]; i++) {
        if (string_starts_with(db->countries[i].name, searched)) {
            cur_node = append_item(cur_node, &db->countries[i]);
            if (head == NULL) head = cur_node;
            results++;
        }
    }

    if (! results) {
        puts("No result found");
    } else {
        cur_node = head;
        while (cur_node != NULL) {
            print_country(cur_node->data);
            cur_node = cur_node->next;
        }

        free_list(head);
    }

    return 0;
}

int search_jobs(struct db *db) {
    tables_metadata[JOB].print_buf(db, db->header.n_recorded[JOB]);
    return 0;
}

int search_industries(struct db *db) {
    tables_metadata[INDUSTRY].print_buf(db, db->header.n_recorded[INDUSTRY]);
    return 0;
}

int search_groups(struct db *db) {
    tables_metadata[GROUP].print_buf(db, db->header.n_recorded[GROUP]);
    return 0;
}
