/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Generic search by numeric index
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <limits.h>
#include <string.h>

#include "db_file/catalog.h"
#include "search/num_index_search.h"
#include "utils/linked_list.h"
#include "utils/string_utils.h"

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
unsigned find_first_num_index(struct db *db, unsigned searched, int start,
                            int stop, unsigned found, enum num_index type) {
    struct num_entity index;
    unsigned middle = (start+stop) / 2;
    unsigned offset = db->header.offset_num_index[type] + middle * sizeof(struct num_entity);

    // read the index
    fseek(db->dat_file, offset, SEEK_SET);
    memset(&index, 0, sizeof(struct num_entity));
    fread(&index, sizeof(struct num_entity), 1, db->dat_file);

    // stop condition
    if (start > stop) {
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

/* HEADER IMPLEMENTATION */

struct search_result search_by_num_index(struct db *db, enum num_index type, unsigned searched) {
    unsigned index_offset;          // first offset matching
    struct num_entity index;        // index entity found
    void *found;                    // record found
    unsigned end;                   // last offset

    // results initialization
    struct search_result res = {
        .result_count = 0,
        .head = NULL,
        .tail = NULL,
    };
    
    const struct num_index_metadata *index_info = &num_indexes_metadata[type];
    const struct table_metadata *table_info = &tables_metadata[index_info->table];

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
            res.tail = append_item(res.tail, found);
            if (res.head == NULL) res.head = res.tail;
            res.result_count++;
        }

        index_offset += sizeof(struct num_entity);
    }

    return res;
}
