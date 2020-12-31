/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database file management:
 *  - database file creation
 *  - database file deletion
 *  - data import (from csv files to dat file)
 *  - data export (from dat file to csv files)
 *  - metadata display
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "db_file/admin.h"
#include "db_file/header.h"
#include "db_file/alpha_index.h"
#include "db_file/num_index.h"
#include "db_file/open_close.h"
#include "utils/logger.h"
#include "utils/system.h"

/* PRIVATE FUNCTION */

/**
 * Creates the empty tables
 * 
 * @param db: database information stored in RAM
 *
 * @return either:
 *      the number of tables successfully created
 *      -1 if an error occured (errno is set)
 */
int create_empty_tables(struct db *db) {
    char *buffer;   // empty tuple buffer
    enum table i;   // table index
    unsigned i_tup; // tuple index

    // create empty tables tuples
    for (i = 0; i < TAB_COUNT; i++) {
        const struct table_metadata *table = &tables_metadata[i];

        buffer = malloc(table->size);
        if (buffer == NULL) {
            return -1;
        }

        memset(buffer, 0, table->size);
        strcpy(buffer, table->prefix);

        for (i_tup = 0; i_tup < table->n_reserved; i_tup++) {
            if (fwrite(buffer, table->size, 1, db->dat_file) != 1) {
                free(buffer);
                return -1;
            }
        }

        free(buffer);
    }

    return i;
}

/**
 * Creates the empty numeric indexes
 * 
 * @param db: database information stored in RAM
 *
 * @return either:
 *      the number of indexes successfully created
 *      -1 if an error occured (errno is set)
 */
int create_empty_num_indexes(struct db *db) {
    struct num_entity tuple;    // empty tuple buffer
    enum num_index i;           // numeric index index
    unsigned i_tup;             // tuple index

    for (i = 0; i < NUM_INDEX_COUNT; i++) {
        const struct num_index_metadata *index = &num_indexes_metadata[i];

        memset(&tuple, 0, sizeof(struct num_entity));
        strcpy(tuple.type, index->prefix);

        for (i_tup = 0; i_tup < db->header.n_rec_table[index->table]; i_tup++) {
            if (fwrite(&tuple, sizeof(struct num_entity), 1, db->dat_file) != 1) {
                return -1;
            }
        }
    }

    return i;
}

/**
 * Creates the empty alphanumeric indexes
 * 
 * @param db: database information stored in RAM
 *
 * @return either:
 *      the number of indexes successfully created
 *      -1 if an error occured (errno is set)
 */
int create_empty_alpha_indexes(struct db *db) {
    struct alpha_entity tuple;  // empty tuple buffer
    enum alpha_index i;         // numeric index index
    unsigned i_tup;             // tuple index

    for (i = 0; i < ALPHA_INDEX_COUNT; i++) {
        const struct alpha_index_metadata *index = &alpha_indexes_metadata[i];

        memset(&tuple, 0, sizeof(struct alpha_entity));
        strcpy(tuple.type, index->prefix);

        for (i_tup = 0; i_tup < db->header.n_rec_table[index->table]; i_tup++) {
            if (fwrite(&tuple, sizeof(struct alpha_entity), 1, db->dat_file) != 1) {
                return -1;
            }
        }
    }

    return i;
}

/* HEADER IMPLEMENTATION */

int create_db(struct db *db) {
    // open database in write mode
    if (open_db(db, WRITE)) {
        puts("An error occured on database file opening: please refer to log file for details");
        return -1;
    }

    // create the header & stop if an error occured
    if (create_header(db) < 0) {
        log_info(db, "Creating database file header", strerror(errno));
        printf("An error occured on header creation: %s\n", strerror(errno));
        return -1;
    }

    // create empty tables & stop if an error occured
    if (create_empty_tables(db) < 0) {
        log_info(db, "Creating database file empty tables", strerror(errno));
        printf("An error occured on empty tables creation: %s\n", strerror(errno));
        return -1;
    }

    // create empty numeric indexes & stop if an error occured
    if (create_empty_num_indexes(db) < 0) {
        log_info(db, "Creating database file empty numeric indexes", strerror(errno));
        printf("An error occured on empty numeric indexes creation: %s\n", strerror(errno));
        return -1;
    }

    // create empty alphanumeric indexes & stop if an error occured
    if (create_empty_alpha_indexes(db) < 0) {
        log_info(db, "Creating database file empty alphanumeric indexes", strerror(errno));
        printf("An error occured on empty alphanumeric indexes creation: %s\n", strerror(errno));
        return -1;
    }

    log_info(db, "Database file creation", "Success");
    printf("Database %s sucessfully created\n", db->header.db_name);

    // reopen database in read mode
    open_db(db, READ);

    return 0;
}

int delete_db(struct db *db) {
    close_db(db);
    if (remove(db->dat_file_path) == 0) {
        log_info(db, "Deleting database file", "Success");
        printf("Database file %s sucessfully deleted.\n", db->header.db_name);

        // delete the header & buffers
        memset(&db->header, 0, sizeof(struct header));
        log_info(db, "Deleting database file", "Header cleaned");

        memset(&db->countries, 0, sizeof(struct country) * N_RES_CTR);
        memset(&db->jobs, 0, sizeof(struct job) * N_RES_JOB);
        memset(&db->industries, 0, sizeof(struct industry) * N_RES_IND);
        memset(&db->groups, 0, sizeof(struct group) * N_RES_GRP);

        return 0;
    }
    log_error(db, "Deleting database file");
    perror("Error while deleting database file");
    return -1;
}

int import(struct db *db) {
    enum table i;                       // table index
    char log_from[64];                  // log method message
    char log_msg[1024];                 // log message
    FILE *csv_file;                     // csv file pointer
    char line[CSV_BUF_LEN];             // csv line
    int tab_error_count = 0;            // count of tables not updated

    // if there is no database, import is impossible
    if (db->dat_file == NULL) {
        log_info(db, "Importing data", "No database file available");
        puts("Impossible: no databse file available");
        return -1;
    }

    // reopen database file in append mode
    open_db(db, APPEND);

    for (i = 0; i < TAB_COUNT; i++) {
        int rec_count = 0;  // number of new tuples successfully recorded
        const struct table_metadata *table = &tables_metadata[i];

        // set where we are
        sprintf(log_from, "Importing data to %s table", table->display_name);

        // open the csv file: rb for consistent treatment of end of line symbols (depending on the OS)
        csv_file = fopen(table->csv_path, "rb");
        if (csv_file == NULL) {
            log_error(db, log_from);
            perror(log_from);
            tab_error_count++;
            continue;
        }

        // place the pointer to the offset of the table to import
        fseek(db->dat_file, db->header.offset_table[i], SEEK_SET);

        // skip the csv header
        fgets(line, CSV_BUF_LEN, csv_file);

        // then write each tuple & count successful new records
        while (fgets(line, CSV_BUF_LEN, csv_file) != NULL) {
            rec_count += (*table->import)(db, line);
        }

        // close the csv file
        fclose(csv_file);

        // update the header infos
        db->header.n_rec_table[i] = rec_count;
        fseek(db->dat_file, 0, SEEK_SET);
        fwrite(&db->header, sizeof(struct header), 1, db->dat_file);

        // log info
        sprintf(log_msg, "%d new records", rec_count);
        log_info(db, log_from, log_msg);
        printf("%-35s %20s\n", log_from, log_msg);
    }

    // log info
    if (tab_error_count != 0) printf("\nImport error on %d table(s)\n", tab_error_count);
    else puts("\nAll tables have been suceessfully updated\n");

    // create numeric indexes
    // TODO replace by loop
    if (create_num_index(db, COMP_BY_GROUP_ID) < 0) {
        log_info(db, "Creating company by group id index", strerror(errno));
        printf("An error occured on company by group id index creation: %s\n", strerror(errno));
        return -1;
    } else {
        log_info(db, "Creating company by group id index", "Success");
        puts("Company by group id index successfully created");
    }

    if (create_num_index(db, PERS_BY_COMP_ID) < 0) {
        log_info(db, "Creating person by company id index", strerror(errno));
        printf("An error occured on person by company id index creation: %s\n", strerror(errno));
        return -1;
    } else {
        log_info(db, "Creating person by company id index", "Success");
        puts("Person by company id index successfully created");
    }

    // create alphanumeric index
    if (create_alpha_index(db, PERS_BY_LASTNAME) < 0) {
        log_info(db, "Creating person by lastname index", strerror(errno));
        printf("An error occured on person by lastname index creation: %s\n", strerror(errno));
        return -1;
    } else {
        log_info(db, "Creating person by lastname index", "Success");
        puts("Person by lastname index successfully created");
    }

    // reopen database file in read mode
    open_db(db, READ);

    return tab_error_count;
}

int export(struct db *db) {
    enum table i;               // table index
    int tab_error_count = 0;    // count of tables not successfully exported
    char sdt[32];               // string formatted date time
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    // if there is no database, export is impossible
    if (db->dat_file == NULL) {
        log_info(db, "Exporting data", "No database file available");
        puts("Impossible: no databse file available");
        return -1;
    }

    // create the directory if it doesn't exist
    make_sub_dir(EXP_DIR);

    // format the date time
    strftime(sdt, 32, "%F_%H-%M-%S", tm);

    for (i = 0; i < TAB_COUNT; i++) {
        char log_from[64];      // log from
        char log_msg[255];      // log message
        char csv_path[255];     // csv file path
        unsigned j = 0;
        unsigned n_rec = 0;
        const struct table_metadata *table = &tables_metadata[i];

        sprintf(log_from, "Exporting data from %s table", table->display_name);

        // format the csv file path
        sprintf(csv_path, EXP_DIR DIR_SEP"%s_Export_%s.csv", table->display_name, sdt);

        // try to open the csv file
        if ((db->csv_file = fopen(csv_path, "w")) == NULL) {
            log_error(db, log_from);
            perror(log_from);
            tab_error_count++;
            continue;
        }

        // print the csv header
        fprintf(db->csv_file, "%s\n", table->csv_header);

        // place the pointer at the first tuple
        fseek(db->dat_file, db->header.offset_table[i], SEEK_SET);

        for (j = 0; j < db->header.n_rec_table[i]; j++) {
            n_rec += (*table->export)(db);
        }

        fclose(db->csv_file);

        // log info
        if (db->header.n_rec_table[i] == 0) {
            strcpy(log_msg, "no records to export");
        } else if (n_rec == db->header.n_rec_table[i]) {
            sprintf(log_msg, "%d records successfully exported", n_rec);
        } else {
            sprintf(log_msg, "error on %d record(s) export (%d successfully exported)",
                        db->header.n_rec_table[i] - n_rec, n_rec);
        }
        log_info(db, log_from, log_msg);
        printf("%-39s %40s\n", log_from, log_msg);
    }

    return tab_error_count;
}

int display_metadata(struct db *db) {
    enum table i;

    if (db->dat_file == NULL) {
        printf("Impossible: no database file opened\n");
        return -1;
    }

    printf("Database name: %s\n", db->header.db_name);
    printf("Database size: %d bytes\n", db->header.size);
    puts("");

    for (i = 0; i < TAB_COUNT; i++) {
        printf("%s table:\n", tables_metadata[i].display_name);
        printf("    %-16s %10d records\n", "Space occupied", db->header.n_rec_table[i]);
        printf("    %-16s %10d records\n", "Space left", db->header.n_res_table[i] - db->header.n_rec_table[i]);
        printf("    %-16s %10d records\n", "Total space", db->header.n_res_table[i]);
        puts("");
    }
    return 0;
}
