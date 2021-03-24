/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Test the search by alphanumeric index on the person by lastname index
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/open_close.h"
#include "search/alpha_index_search.h"
#include "db_file/open_close.h"
#include "utils/system.h"

#include "test_helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int failures = 0;

void test(struct db *db, enum alpha_index alpha_index, char *tested, unsigned *expected_ids, unsigned expected_size) {
    printf("- searching for '%s'\n", tested);

    const struct alpha_index_metadata *index = &alpha_indexes_metadata[alpha_index];

    struct search_result res = search_by_alpha_index(db, alpha_index, tested);
    unsigned *sorted_ids = malloc(sizeof(unsigned) * res.result_count);

    sort_ids(index->table, res.head, sorted_ids, expected_size);

    ASSERT_EQUALS(expected_size, res.result_count);
    ASSERT_ARRAY_EQUALS(expected_ids, sorted_ids, expected_size);

    free_list(res.head, 1);
    free(sorted_ids);
}

int main() {
    struct db db;

    // start the application
    make_sub_dir(DAT_DIR);
    db.log_file = fopen(DAT_DIR DIR_SEP"test_alpha_index_search.log", "a");
    db.app_mode = USER;
    db.dat_file = NULL;
    strcpy(db.dat_file_path, DAT_DIR DIR_SEP "db_clients.dat");
    open_db(&db, READ);

    puts("\nalpha index search on the person by last name index\n");

    // cut -d ';' -f 1,6 data_import/DB_Person.csv | grep -i ';bina'
    // cut -d ';' -f 1,6 data_import/DB_Person.csv | grep -i ';bina' | wc -l
    test(&db, PERS_BY_LASTNAME, "bina", (unsigned[]){ 129235, 257203, 274691, 296968, 415493, 486326,
            490167, 494765, 548039, 767376, 800436, 868649, 935852, 1504867, 1507159, 1513709 }, 16);

    test(&db, PERS_BY_LASTNAME, "binaa", (unsigned[]){0}, 0);

    return failures;
}
