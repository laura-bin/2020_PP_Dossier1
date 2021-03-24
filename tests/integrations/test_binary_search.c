/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Test the binary search on group, company and person tables
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/open_close.h"
#include "search/binary_search.h"
#include "db_file/open_close.h"
#include "utils/system.h"

#include "test_helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int failures = 0;

void test(struct db *db, enum table table, int tested, unsigned expected_id) {
    printf("- searching for '%d'\n", tested);

    const struct table_metadata *table_info = &tables_metadata[table];
   
    unsigned offset = binary_search(db, tested, 0, db->header.n_rec_table[table]-1, table);
    if (offset == UINT_MAX) {
        fprintf(stderr, "got UINT_MAX for table %d, test %d\n", table, tested);
        failures++;
        return;
    }
    
    void *data = (table_info->read)(db, offset);
    unsigned id = get_id(table, data);

    ASSERT_EQUALS(expected_id, id);
}

int main() {
    struct db db;

    // start the application
    make_sub_dir(DAT_DIR);
    db.log_file = fopen(DAT_DIR DIR_SEP"test_binary_search.log", "a");
    db.app_mode = USER;
    db.dat_file = NULL;
    strcpy(db.dat_file_path, DAT_DIR DIR_SEP "db_clients.dat");
    open_db(&db, READ);

    puts("\nbinary search on the company table\n");
    // first
    test(&db, COMPANY, 1, 108);
    test(&db, COMPANY, 108, 108);

    // last
    test(&db, COMPANY, 686255, 686255);
    test(&db, COMPANY, 690000, 686255);

    // exact
    test(&db, COMPANY, 120, 120);

    puts("\nbinary search on the group table\n");

    // first
    test(&db, GROUP, 1, 1);

    // last
    test(&db, GROUP, 2245, 2245);
    test(&db, GROUP, 3000, 2245);

    // exact
    test(&db, GROUP, 2239, 2239);

    puts("\nbinary search on the person table\n");

    // first
    test(&db, PERSON, 1, 5);
    test(&db, PERSON, 5, 5);

    // last
    test(&db, PERSON, 1528210, 1528210);
    test(&db, PERSON, 2000000, 1528210);

    // exact
    test(&db, PERSON, 200, 200);

    return failures;
}
