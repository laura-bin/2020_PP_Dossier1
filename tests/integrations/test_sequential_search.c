/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Test the sequantial search in country, job, industry and group tables
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/open_close.h"
#include "search/sequential_search.h"
#include "db_file/open_close.h"
#include "utils/system.h"

#include <stdio.h>
#include <string.h>

int failures = 0;

#define ASSERT_EQUALS(expect, value) do {\
        printf(#expect " == " #value ": %u == %u: ", value, expect); \
        fflush(stdout); \
        if (expect == value) { \
            printf("v\n"); \
        } else { \
            failures++; \
            printf("x\n"); \
        } \
    } while (0)


void test(struct db *db, enum table table, char *tested, unsigned *expected_ids, unsigned expected_size) {
    printf("- searching for '%s'\n", tested);
    struct search_result res = sequential_search(db, table, tested);
    
    struct node *node = res.head;
    unsigned count = 0;

    switch (table) {
    case COUNTRY:
        while (node) {
            struct country *country = node->data;

            ASSERT_EQUALS(expected_ids[count], country->id);

            node = node->next;
            count++;
        }
        break;
    case JOB:
        while (node) {
            struct job *job = node->data;

            ASSERT_EQUALS(expected_ids[count], job->id);

            node = node->next;
            count++;
        }
        break;
    case INDUSTRY:
        while (node) {
            struct industry *industry = node->data;

            ASSERT_EQUALS(expected_ids[count], industry->id);

            node = node->next;
            count++;
        }
        break;
    case GROUP:
        while (node) {
            struct group *group = node->data;

            ASSERT_EQUALS(expected_ids[count], group->id);

            node = node->next;
            count++;
        }
        break;
    
    default:
        break;
    }

    ASSERT_EQUALS(expected_size, count);
}

int main() {
    struct db db;

    // start the application
    make_sub_dir(DAT_DIR);
    db.log_file = fopen(DAT_DIR DIR_SEP"test_sequential_search.log", "a");
    db.app_mode = USER;
    db.dat_file = NULL;
    strcpy(db.dat_file_path, DAT_DIR DIR_SEP "db_clients.dat");
    open_db(&db, READ);

    puts("\nsequential search on the country table\n");

    // nominal case
    // grep -i be data_import/DB_Country.csv | cut -d';' -f1
    test(&db, COUNTRY, "be", (unsigned[]){2, 17, 20}, 3);

    // empty string
    // grep -i ""be"" data_import/DB_Country.csv | cut -d';' -f1
    test(&db, COUNTRY, "", (unsigned[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
        16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30}, 30);

    // no result found
    // grep -i aaa data_import/DB_Country.csv | cut -d';' -f1
    test(&db,  COUNTRY, "aaa", (unsigned[]){0}, 0);

    puts("\nsequential search on the job table\n");

    // nominal case
    // grep -i project data_import/DB_Job.csv | cut -d';' -f1
    test(&db, JOB, "project", (unsigned[]){9, 42, 85}, 3);

    // no result found
    // grep -i aaa data_import/DB_Job.csv | cut -d';' -f1
    test(&db, JOB, "aaa", (unsigned[]){0}, 0);

    puts("\nsequential search on the industry table\n");

    // nominal case
    // grep -i tele data_import/DB_Industry.csv | cut -d';' -f1
    test(&db, INDUSTRY, "tele", (unsigned[]){26, 57}, 2);

    // no result found
    // grep -i aaa data_import/DB_Industry.csv | cut -d';' -f1
    test(&db, INDUSTRY, "aaa", (unsigned[]){0}, 0);

    puts("\nsequential search on the group table\n");

    // nominal case
    // grep -i tech data_import/DB_Group.csv | cut -d';' -f1
    test(&db, GROUP, "tech", (unsigned[]){64, 89, 277, 496, 687, 849, 881, 894, 920, 945, 981,
        1000, 1186, 1239, 1508, 1514, 1561, 1808, 1953, 1954, 1975, 1976, 1977, 2054, 2196}, 25);

    // no result found
    // grep -i aaa data_import/DB_Group.csv | cut -d';' -f1
    test(&db, GROUP, "aaa", (unsigned[]){0}, 0);

    return failures;
}
