/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Generic binary search
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "search/binary_search.h"

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

    if (start > stop || found == 0) {
        return offset;
    }

    if (found < 0) {
        stop = middle - 1;
    } else {
        start = middle + 1;
    }

    return binary_search(db, searched, start, stop, table_type);
}
