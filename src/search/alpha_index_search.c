/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database file searches by alphanumeric index:
 *  - search people by lastname prefix
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "db_file/catalog.h"
#include "search/alpha_index_search.h"
#include "table/person.h"
#include "utils/string_comparison.h"
#include "ui/ui-utils.h"

/* PRIVATE FUNCTION */

/**
 * Finds the first alphanumeric index matching with the searched prefix
 *
 * @param db: database information stored in RAM
 * @param prefix: prefix searched
 * @param index_offset: head index
 *
 * @return either
 *      the offset of the first matched person index
 *      UINTMAX if no result has been found
 */
unsigned find_first_index(struct db *db, char *prefix, enum alpha_index type) {
    struct alpha_entity index;
    int comparison_result;
    unsigned index_offset = db->header.offset_tree[type];

    while (1) {
        // stop searching on leaf node
        if (index_offset == UINT_MAX) {
            return UINT_MAX;
        }

        // read the index info
        memset(&index, 0, sizeof(struct alpha_entity));
        fseek(db->dat_file, index_offset, SEEK_SET);
        if (fread(&index, sizeof(struct alpha_entity), 1, db->dat_file) != 1) {
            return UINT_MAX;
        }

        // compare the person lastname with the prefix giver by the user
        comparison_result = start_with_icase(index.value, prefix);

        // if they match, return the index offset
        if (comparison_result == 0) {
            return index_offset;
        }

        // else continue the search
        if (comparison_result < 0) {
            index_offset = index.left;
        } else {
            index_offset = index.rigth;
        }
    }
}

/**
 * Searches records by an alphanumeric index
 * and shows the paginated list of results
 *
 * @param db: database information stored in RAM
 * @param type: alphanumeric index type
 */
int search_by_alpha_index(struct db *db, enum alpha_index type) {
    char searched[MAX_LEN];         // substring searched
    unsigned index_offset;          // head node of the results tree
    struct alpha_entity index;      // index entity found
    void *found;                    // record found
    struct node *head = NULL;       // linked list head
    struct node *cur_node = NULL;   // linked list current node
    unsigned results = 0;           // number of records found
    unsigned end;                   // index last offset
    
    const struct index_metadata *index_info = &alpha_indexes_metadata[type];

    // get the user input
    printf("Enter the substring searched: ");
    get_text_input(searched, MAX_LEN);

    // get the first index matching with the searched prefix
    index_offset = find_first_index(db, searched, type);

    // create the list of results
    end = db->header.offset_alpha_index[type] + db->header.n_rec_table[index_info->table] * sizeof(struct alpha_entity);
    while (index_offset < end) {
        // read the index
        fseek(db->dat_file, index_offset, SEEK_SET);
        memset(&index, 0, sizeof(struct alpha_entity));
        fread(&index, sizeof(struct alpha_entity), 1, db->dat_file);

        // stop if the prefix doesn't match the index value
        if (start_with_icase(index.value, searched)) {
            break;
        }

        // else read the associated record
        found = (*index_info->read)(db, index.offset);

        // and add it to the list of results
        if (found != NULL) {
            cur_node = append_item(cur_node, found);
            if (head == NULL) head = cur_node;
            results++;
        }

        index_offset += sizeof(struct alpha_entity);
    }

    paginate(results, head, index_info->print, index_info->print_header);
    free_list(head, 1);
    return 0;
}

/* HEADER IMPLEMENTATION */

int search_people_by_lastname(struct db *db) {
    return search_by_alpha_index(db, PERS_BY_LASTNAME);
}
