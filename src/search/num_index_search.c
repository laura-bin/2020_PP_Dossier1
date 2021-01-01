/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database file searches by numerc index:
 *  - search people by company id
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "db_file/catalog.h"
#include "search/num_index_search.h"
#include "table/person.h"
#include "ui/ui-utils.h"
#include "utils/string_comparison.h"

/* PRIVATE FUNCTION */

/**
 * Finds the first numeric index matching with the searched number
 * (binary search non optimized adaptation)
 *
 * @param db: database information stored in RAM
 * @param searched: number searched
 * @param start: start index (0 on the first call)
 * @param stop: stop index (number of recorded indexes -1 on the first call)
 * @param found: found boolean
 * @param type: index type
 *
 * @return either
 *      the offset of the first matched numeric index
 *      UINTMAX if no result has been found
 */
unsigned find_first_num_index(struct db *db, unsigned searched, unsigned start,
                            unsigned stop, unsigned found, enum num_index type) {
    struct num_entity index;
    unsigned middle = start + (stop - start) / 2;
    unsigned offset = db->header.offset_num_index[type] + middle * sizeof(struct num_entity);

    // read the index
    fseek(db->dat_file, offset, SEEK_SET);
    memset(&index, 0, sizeof(struct num_entity));
    fread(&index, sizeof(struct num_entity), 1, db->dat_file);

    // stop condition
    if (start == middle) {
        if (searched == index.value || found) {
            if (!found) {
                return offset;
            } else {
                return found;
            }
        } else {
            return UINT_MAX;
        }
    }

    if (searched <= index.value) {
        if (searched == index.value) {
            // if start = 0 || element -1 != searched -> return offset
            found = offset;
        }
        stop = middle - 1;
    } else {
        start = middle + 1;
    }

    return find_first_num_index(db, searched, start, stop, found, type);
}

/**
 * Searches records by an numeric index
 * and shows the paginated list of results
 *
 * @param db: database information stored in RAM
 * @param type: numeric index type
 */
int search_by_num_index(struct db *db, enum num_index type) {
    unsigned searched;              // number searched
    unsigned index_offset;          // first offset matching
    struct num_entity index;        // index entity found
    void *found;                    // record found
    struct node *head = NULL;       // linked list first node
    struct node *last = NULL;       // linked list last node
    unsigned results = 0;           // number of records found
    unsigned end;                   // last offset
    int reversed;                   // reversed order boolean
    
    const struct num_index_metadata *index_info = &num_indexes_metadata[type];
    const struct table_metadata *table_info = &tables_metadata[index_info->table];

    // get the user input
    printf("Enter the number searched: ");
    searched = get_uns_input();

    printf("Print the results in reversed order ? [yes/NO] ");
    reversed = get_yes_input();

    // get the first index matching with the searched prefix
    index_offset = find_first_num_index(db, searched, 0, db->header.n_rec_table[index_info->table]-1, 0, type);

    // create the list of results
    end = db->header.offset_num_index[type] + db->header.n_rec_table[index_info->table] * sizeof(struct num_entity);
    while (index_offset < end) {
        // read the index
        fseek(db->dat_file, index_offset, SEEK_SET);
        memset(&index, 0, sizeof(struct num_entity));
        fread(&index, sizeof(struct num_entity), 1, db->dat_file);

        // stop if the prefix doesn't match the index value
        if (index.value != searched) {
            break;
        }

        // else read the associated record
        found = (*table_info->read)(db, index.offset);

        // and add it to the list of results
        if (found != NULL) {
            last = append_item(last, found);
            if (head == NULL) head = last;
            results++;
        }

        index_offset += sizeof(struct num_entity);
    }

    paginate(results, reversed ? last : head, table_info->print, table_info->print_header, reversed);
    free_list(head, 1);
    return 0;
}

/* HEADER IMPLEMENTATION */


int search_people_by_company_id(struct db *db) {
    search_by_num_index(db, PERS_BY_COMP_ID);
    return 0;
}
