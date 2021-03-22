/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database file sequential searches in code tables (country, job, industry, group)
 * displayed on the standard output
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "display_search/display_sequential_search.h"
#include "search/sequential_search.h"
#include "ui/ui_utils.h"

/* PRIVATE FUNCTION */

/**
 * Searches records in the RAM stored buffer (sequential search)
 * and displays the paginated list of results
 *
 * @param db: database information stored in RAM
 * @param tab: table enum
 */
int display_sequential_search(struct db *db, enum table tab) {
    char searched[MAX_LEN];         // substring searched
    int reversed;                   // reversed order boolean
    struct search_result res;       // results found

    const struct table_metadata *table = &tables_metadata[tab];

    // get the user inputs
    printf("Enter the substring searched: ");
    get_text_input(searched, MAX_LEN);

    printf("Print the results in reversed order ? [yes/NO] ");
    reversed = get_yes_input();

    // get the results and display the paginated list of results
    res = sequential_search(db, tab, searched);
    paginate(res.result_count, reversed ? res.tail : res.head, table->print,
        table->print_header, reversed);
    free_list(res.head, 0);

    return 0;
}

/* HEADER IMPLEMENTATION */

int search_countries(struct db *db) {
    return display_sequential_search(db, COUNTRY);
}

int search_jobs(struct db *db) {
    return display_sequential_search(db, JOB);
}

int search_industries(struct db *db) {
    return display_sequential_search(db, INDUSTRY);
}

int search_groups(struct db *db) {
    return display_sequential_search(db, GROUP);
}
