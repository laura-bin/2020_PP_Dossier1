/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Test the search by numeric index on the person by company id index
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/open_close.h"
#include "search/num_index_search.h"
#include "db_file/open_close.h"
#include "utils/system.h"

#include "test_helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int failures = 0;

void test(struct db *db, enum num_index num_index, unsigned tested, unsigned *expected_ids, unsigned expected_size) {
    printf("- searching for '%u'\n", tested);

    const struct num_index_metadata *index = &num_indexes_metadata[num_index];

    struct search_result res = search_by_num_index(db, num_index, tested);
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
    db.log_file = fopen(DAT_DIR DIR_SEP"test_num_index_search.log", "a");
    db.app_mode = USER;
    db.dat_file = NULL;
    strcpy(db.dat_file_path, DAT_DIR DIR_SEP "db_clients.dat");
    open_db(&db, READ);

    puts("\nnum index search on the person by company id index\n");

    // cut -d ';' -f 1-2 data_import/DB_Person.csv | grep ';110$'
    test(&db, PERS_BY_COMP_ID, 110, (unsigned[]){ 192, 193, 225424 }, 3);

    puts("\nnum index search on the company by group id index\n");

    test(&db, COMP_BY_GROUP_ID, 1, (unsigned[]){ 74182, 124660, 130480, 148087, 215439, 232151,
            257625, 265046, 316176, 328777, 351926, 417527, 463378, 556965, 643690 }, 15);
    test(&db, COMP_BY_GROUP_ID, 110, (unsigned[]){ 123128 }, 1);
    test(&db, COMP_BY_GROUP_ID, 417527, NULL, 0);
    test(&db, COMP_BY_GROUP_ID, 2569173326, NULL, 0);
    

    return failures;
}
