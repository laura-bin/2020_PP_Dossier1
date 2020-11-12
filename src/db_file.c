/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Database acces :
*   - creation of the empty file
*   - deletion of the database file
*   - metadata display
*   - data import from csv files
*   - data export (test function)
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "db_file.h"
#include "table/country.h"
#include "system.h"
#include "utils.h"

/****************************************************************************************
* Opens the database in a defined mode
* if it's opened in read mode, gets the metadata and fills the buffers
****************************************************************************************/
int open_db(struct db *db, enum opening_mode mode) {
    char log_msg[64];

    switch (mode) {
        case READ:
            strcpy(log_msg, "Opening database file in read mode");
            db->dat_file = fopen(db->dat_file_path, "rb");
            break;

        case WRITE:
            // init log message
            strcpy(log_msg, "Opening database file in write mode");
            db->dat_file = fopen(db->dat_file_path, "wb");
            break;

        case APPEND:
            // init log message
            strcpy(log_msg, "Opening database file in append mode");
            db->dat_file = fopen(db->dat_file_path, "rb+");
            break;

        default:
            break;
    }

    if (db->dat_file == NULL) {
        log_error(db, log_msg);
        return 1;
    }

    // load the header in write or append mode
    if (mode != WRITE) {
        fseek(db->dat_file, 0, SEEK_SET);
        if (fread(&db->header, sizeof(struct header), 1, db->dat_file) == 1) {
            log_info(db, log_msg, "Header loaded");
        }
    }

    // TODO fill the buffers
    
    log_info(db, log_msg, "Database file successfully opened");
    return 0;
}

/****************************************************************************************
* Closes the database file
****************************************************************************************/
int close_db(struct db *db) {
    if (db->dat_file != NULL) {
        fclose(db->dat_file);
        db->dat_file = NULL;
        log_info(db, "Closing database file", "Database file succesfully closed");
        return 0;
    }
    return 1;
}

/****************************************************************************************
* Creates an empty DB file (.dat)
****************************************************************************************/
int create_db(struct db *db) {
    enum table i;           // index used to create each table
    unsigned j = 0;         // index used to create each empty tuple
    size_t offset;          // offset of each entity (table/index)
    char *buffer;           // empty tuple buffer
    size_t max_size = 0;    // max entity size used to initialize the buffer

    log_info(db, "Database file creation", "Starting...");
    puts("Starting database file creation...\n");

    // close database file if a file is opened
    close_db(db);

    // then reopen database file in write mode (file is truncated)
    if ((db->dat_file = fopen(db->dat_file_path, "wb")) == NULL) {
        log_error(db, "Database file creation");
    } else
    log_info(db, "Database file creation", "Database file opened in write mode");

    // create header
    memset(&db->header, 0, sizeof(struct header));
    strcpy(db->header.db_name, "db_clients");
    offset = sizeof(struct header);

    for (i = 0; i < TAB_COUNT; i++) {
        const struct table_metadata *table = &tables_metadata[i];

        db->header.n_reserved[i] = table->n_reserved;
        db->header.offset[i] = offset;
        db->header.n_recorded[i] = 0;

        offset += table->n_reserved * table->size;
        max_size = max_size > table->size ? max_size : table->size;
    }
    db->header.size = offset;
    fwrite(&db->header, sizeof(db->header), 1, db->dat_file);

    // create empty tables
    buffer = malloc(max_size);

    for (i = 0; i < TAB_COUNT; i++) {
        const struct table_metadata *table = &tables_metadata[i];

        memset(buffer, 0, max_size);
        strcpy(buffer, table->prefix);

        for (j = 0; j < table->n_reserved; j++) {
            fwrite(buffer, table->size, 1, db->dat_file);
        }
    }
    free(buffer);

    printf("Database %s sucessfully created\n", db->header.db_name);
    log_info(db, "Database file creation", "File successfully created");

    // reopen database in read mode
    close_db(db);
    open_db(db, READ);

    return 0;
}

/****************************************************************************************
* Deletes the database file
****************************************************************************************/
int delete_db(struct db *db) {
    close_db(db);
    if (remove(db->dat_file_path) == 0) {
        log_info(db, "Deleting database", "Database file successfully deleted");
        printf("Database file %s sucessfully deleted.\n", db->header.db_name);

        // delete the header & buffers
        memset(&db->header, 0, sizeof(struct header));
        log_info(db, "Deleting database", "Header cleaned");

        memset(&db->countries, 0, sizeof(struct country) * N_RES_CTR);
        memset(&db->jobs, 0, sizeof(struct job) * N_RES_JOB);
        memset(&db->industries, 0, sizeof(struct industry) * N_RES_IND);
        memset(&db->groups, 0, sizeof(struct group) * N_RES_GRP);

        return 0;
    }
    log_error(db, "Deleting database file");
    perror("Error while deleting database file");
    return 1;
}

/****************************************************************************************
* Imports data from csv files to dat file
* returns 0 if all tables have been successfully updated
* -1 if there is no database
* else the number of tables for which there was an error while import
****************************************************************************************/
int import(struct db *db) {
    enum table i;                       // table index
    FILE *csv_file;                     // csv file pointer
    const unsigned buf_len = 1024;      // line buffer length
    char line[buf_len];                 // csv line
    int tab_error_count = 0;            // count of tables not updated

    // if there is no database, import is impossible
    if (db->dat_file == NULL) {
        log_info(db, "Importing data", "No database file available");
        puts("Impossible: no databse file available");
        return -1;
    }

    // reopen database file in write mode
    close_db(db);
    open_db(db, APPEND);

    for (i = 0; i < TAB_COUNT; i++) {
        char log_msg[1024]; // log message
        int rec_count = 0;  // number of new tuples successfully recorded
        const struct table_metadata *table = &tables_metadata[i];
        
        // open the csv file: rb for consistent treatment of end of line symbols (depending on the OS)
        csv_file = fopen(table->csv_path, "rb");
        if (csv_file == NULL) {
            sprintf(log_msg, "Importing data from %s", table->csv_path);
            log_error(db, log_msg);
            perror(log_msg);
            tab_error_count++;
            continue;
        }

        sprintf(log_msg, "%s successfully opened", table->csv_path);
        log_info(db, "Importing data", log_msg);

        // place the pointer to the offset of the table to import
        fseek(db->dat_file, db->header.offset[i], SEEK_SET);

        // skip the csv header
        fgets(line, buf_len, csv_file);

        // then write each tuple & count successful new records
        while (fgets(line, buf_len, csv_file) != NULL) {
            rec_count += (*table->import)(db, line);
        }

        // close the csv file
        fclose(csv_file);

        // update the header infos
        db->header.n_recorded[i] = rec_count;
        fseek(db->dat_file, 0, SEEK_SET);
        fwrite(&db->header, sizeof(struct header), 1, db->dat_file);

        // log info
        sprintf(log_msg, "Table %-8s %6d new records", table->display_name, rec_count);
        log_info(db, "Importing data", log_msg);
        puts(log_msg);
    }

    // log info
    if (tab_error_count != 0) printf("\nImport error on %d table(s)\n", tab_error_count);
    else puts("\nAll tables have been suceessfully updated");

    // reopen database file in read mode
    close_db(db);
    open_db(db, READ);

    return tab_error_count;
}

/****************************************************************************************
* Exports data from dat file to csv files
* returns 0 if all tables have been successfully exportes
* -1 if there is no database
* else the number of tables for which there was an error while exporting
****************************************************************************************/
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
        char log_msg[255];      // log message
        char csv_path[255];     // csv file path
        unsigned j = 0;
        unsigned n_rec = 0;
        const struct table_metadata *table = &tables_metadata[i];

        // format the csv file path
        sprintf(csv_path, EXP_DIR DIR_SEP"%s_Export_%s.csv", table->display_name, sdt);

        // try to open the csv file
        if ((db->csv_file = fopen(csv_path, "w")) == NULL) {
            sprintf(log_msg, "Exporting %s table", table->display_name);
            log_error(db, log_msg);
            perror(log_msg);
            tab_error_count++;
            continue;
        }

        // print the csv header
        fprintf(db->csv_file, "%s\n", table->csv_header);

        // place the pointer at the first tuple
        fseek(db->dat_file, db->header.offset[i], SEEK_SET);

        for (j = 0; j < db->header.n_recorded[i]; j++) {
            n_rec += (*table->export)(db);
        }

        fclose(db->csv_file);

        // log info
        if (db->header.n_recorded[i] == 0) {
            sprintf(log_msg, "Exporting %s table: no records to export", table->display_name);
        } else if (n_rec == db->header.n_recorded[i]) {
            sprintf(log_msg, "Exporting %s table: %d records successfully exported",
                        table->display_name, n_rec);
        } else {
            sprintf(log_msg, "Exporting %s table: error on %d record(s) export (%d successfully exported)",
                        table->display_name, db->header.n_recorded[i] - n_rec, n_rec);
        }
        log_info(db, "Exporting data", log_msg);
        puts(log_msg);
    }

    return tab_error_count;
}

/****************************************************************************************
* Displays the database metadata (db name, number of reserved locations,
* number of records in each tables, etc.)
****************************************************************************************/
int display_metadata(struct db *db) {
    enum table i;
    
    if (db->dat_file == NULL) {
        printf("Impossible: no database file opened\n");
        log_info(db, "Display metadata", "impossible to show metadata (no file opened)");
        return 1;
    }

    printf("Database name: %s\n", db->header.db_name);
    printf("Database size: %d bytes\n", db->header.size);
    puts("");

    for (i = 0; i < TAB_COUNT; i++) {
        printf("%s table:\n", tables_metadata[i].display_name);
        printf("    %-16s %10d recordings\n", "Space occupied", db->header.n_recorded[i]);
        printf("    %-16s %10d recordings\n", "Space left", db->header.n_reserved[i] - db->header.n_recorded[i]);
        printf("    %-16s %10d recordings\n", "Total space", db->header.n_reserved[i]);
        puts("");
    }

    return 0;
}

int dummy_fct(struct db *db) {
    puts("dummy fct");
    pause_page();
    return 0;
}
