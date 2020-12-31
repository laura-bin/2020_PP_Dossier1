/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database file binary searches on tables ids:
 *  - search company by id
 *  - search person by id
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "search/binary_search.h"
#include "ui/ui-utils.h"
#include "utils/logger.h"

/**
 * Finds the offset of a record matching with a searched id
 * or the nearest result offset
 *
 * @param db: database information stored in RAM
 * @param searched: id searched
 * @param start: start index (0 on the first call)
 * @param stop: stop index (number of recorded indexes -1 on the first call)
 * @param table_type: table_type
 *
 * @return either
 *      the offset of the record found or of the nearest result
 *      UINTMAX if an error occured
 */
unsigned binary_search(struct db *db, unsigned searched, unsigned start,
                            unsigned stop, enum table table_type) {
    int found;
    const struct table_metadata *table_info = &tables_metadata[table_type];

    unsigned middle = start + (stop - start) / 2;
    unsigned offset = db->header.offset_table[table_type] + middle * table_info->size;


    found = (*table_info->compare_id)(db, offset, searched);
    if (found == INT_MAX) {
        return UINT_MAX;
    }

    if (start == middle || found == 0) {
        return offset;
    }

    if (found < 0) {
        stop = middle - 1;
    } else {
        start = middle + 1;
    }

    return binary_search(db, searched, start, stop, table_type);
}

/**
 * Searches records by id and shows detailed list of results
 * (the single record if it was found or the list of 3 nearest results)
 *
 * @param db: database information stored in RAM
 * @param type: table type
 */
int search_by_id(struct db *db, enum table table_type) {
    unsigned searched;              // number searched
    unsigned result_offset;         // offset found
    void *found;                    // record found
    struct node *head = NULL;       // linked list head
    struct node *cur_node = NULL;   // linked list current node
    int results = 1;                // number of results in the list
    unsigned first_offset;          // first valid offset
    unsigned last_offset;           // last valid offset
    int i;

    const struct table_metadata *table_info = &tables_metadata[table_type];

    // get the user input
    printf("Enter the number searched: ");
    searched = get_uns_input();

    // get the record offset matching with the searched id or the nearest result
    result_offset = binary_search(db, searched, 0, db->header.n_rec_table[table_type]-1, table_type);

    if (result_offset == UINT_MAX) {
        log_info(db, "Search by id", strerror(errno));
        printf("\nAn error occured: %s\n", strerror(errno));
    }

    // if the result doesn't match, adjust the offset and set the number of results to 3
    if ((*table_info->compare_id)(db, result_offset, searched)) {
        first_offset = db->header.offset_table[table_type];
        last_offset = first_offset + (db->header.n_rec_table[table_type]-1) * table_info->size;

        // adjust the first offset
        if (result_offset != first_offset) {
            if (result_offset == last_offset) {
                result_offset = last_offset - 2*table_info->size;
            } else {
                result_offset -= table_info->size;
            }
        }

        results = 3;
    }
    
    // create the list of results
    for (i = 0; i < results; i++) {
        found = (*table_info->read)(db, result_offset);
        if (found != NULL) {
            cur_node = append_item(cur_node, found);
            if (head == NULL) {
                head = cur_node;
            }
        }
        result_offset += table_info->size;
    }

    // print the result & free the list
    print_detail_list(results, head, table_info->print_details);
    free_list(head, 1);
    return 0;
}

/* HEADER IMPLEMENTATION */

int search_group_by_id(struct db *db) {
    return search_by_id(db, GROUP);
}

int search_company_by_id(struct db *db) {
    return search_by_id(db, COMPANY);
}

int search_person_by_id(struct db *db) {
    return search_by_id(db, PERSON);
}
