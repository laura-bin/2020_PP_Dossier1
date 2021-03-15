/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database file searches by numeric index displayed on the standard output:
 *  - search people by company id
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "display_search/display_num_index_search.h"
#include "search/num_index_search.h"
#include "table/person.h"
#include "ui/ui-utils.h"

/* PRIVATE FUNCTION */

/**
 * Searches records by numeric index
 * and displays the paginated list of results
 *
 * @param db: database information stored in RAM
 * @param type: index type enum
 */
int display_search_by_num_index(struct db *db, enum num_index type) {
    unsigned searched;          // integer id searched
    int reversed;               // reversed order boolean
    struct search_result res;   // list of results found

    const struct table_metadata *table_info = &tables_metadata[num_indexes_metadata[type].table];
    
    // get the user inputs
    printf("Enter the number searched: ");
    searched = get_uns_input();

    printf("Print the results in reversed order ? [yes/NO] ");
    reversed = get_yes_input();

    // get the results and display the paginated list of results
    res = search_by_num_index(db, PERS_BY_COMP_ID, searched);
    paginate(res.result_count, reversed ? res.tail : res.head, table_info->print,
        table_info->print_header, reversed);
    free_list(res.head, 1);

    return 0;
}

/* HEADER IMPLEMENTATION */

int search_people_by_company_id(struct db *db) {
    return display_search_by_num_index(db, PERS_BY_COMP_ID);
}
