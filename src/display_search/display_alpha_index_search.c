/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Searches by alphanumeric index displayed on the standard output:
 *  - search people by lastname prefix
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "display_search/display_alpha_index_search.h"
#include "search/alpha_index_search.h"
#include "ui/ui-utils.h"

/* PRIVATE FUNCTION */

/**
 * Searches records by alphanumeric index
 * and displays the paginated list of results
 *
 * @param db: database information stored in RAM
 * @param type: index type enum
 */
int display_search_by_alpha_index(struct db *db, enum alpha_index type) {
    char searched[MAX_LEN];         // substring searched
    int reversed;                   // reversed order boolean
    struct search_result res;       // results found

    const struct table_metadata *table_info = &tables_metadata[alpha_indexes_metadata[type].table];

    // get the user inputs
    printf("Enter the substring searched: ");
    get_text_input(searched, MAX_LEN);

    // get the user's choice about the results order
    printf("Print the results in reversed order ? [yes/NO] ");
    reversed = get_yes_input();

    // get the results and display the paginated list of results
    res = search_by_alpha_index(db, PERS_BY_LASTNAME, searched);
    paginate(res.result_count, reversed ? res.tail : res.head, table_info->print,
        table_info->print_header, reversed);
    free_list(res.head, 1);

    return 0;
}

/* HEADER IMPLEMENTATION */

int search_people_by_lastname(struct db *db) {
    return display_search_by_alpha_index(db, PERS_BY_LASTNAME);
}
