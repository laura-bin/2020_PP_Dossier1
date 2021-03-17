/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Generic search by alphanumeric index
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "db_file/catalog.h"
#include "search/alpha_index_search.h"
#include "utils/linked_list.h"
#include "utils/string_comparison.h"

/* PRIVATE FUNCTION */

/**
 * Finds the first alphanumeric index matching with the searched prefix
 *
 * @param db: database information stored in RAM
 * @param prefix: prefix searched
 * @param type: index type
 *
 * @return either
 *      the offset of the first matched alphanumeric index
 *      UINTMAX if no result has been found
 */
unsigned find_first_alpha_index(struct db *db, char *prefix, enum alpha_index type) {
    struct alpha_entity index;
    int comparison_result;
    unsigned index_offset = db->header.offset_tree[type];
    unsigned previous_offset;

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

        // if they match, go to the first matching result
        if (comparison_result == 0) {
            do {
                previous_offset = index_offset;
                index_offset -= sizeof(struct alpha_entity);

                // read the previous value
                memset(&index, 0, sizeof(struct alpha_entity));
                fseek(db->dat_file, index_offset, SEEK_SET);
                if (fread(&index, sizeof(struct alpha_entity), 1, db->dat_file) != 1) {
                    return UINT_MAX;
                }
            } while (!start_with_icase(index.value, prefix));

            return previous_offset;
        }

        // else continue the search
        if (comparison_result < 0) {
            index_offset = index.left;
        } else {
            index_offset = index.rigth;
        }
    }
}

/* HEADER IMPLEMENTATION */

struct search_result search_by_alpha_index(struct db *db, enum alpha_index type, char *searched) {
    unsigned index_offset;          // head node of the results tree
    struct alpha_entity index;      // index entity found
    void *found;                    // record found
    unsigned end;                   // last offset

    // results initialization
    struct search_result res = {
        .result_count = 0,
        .head = NULL,
        .tail = NULL,
    };
    
    const struct alpha_index_metadata *index_info = &alpha_indexes_metadata[type];
    const struct table_metadata *table_info = &tables_metadata[index_info->table];

    // get the first index matching with the searched prefix
    index_offset = find_first_alpha_index(db, searched, type);

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
        found = (*table_info->read)(db, index.offset);

        // and add it to the list of results
        if (found != NULL) {
            res.tail = append_item(res.tail, found);
            if (res.head == NULL) res.head = res.tail;
            res.result_count++;
        }

        index_offset += sizeof(struct alpha_entity);
    }

    return res;
}
