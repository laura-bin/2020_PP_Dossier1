/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Database acces :
*   - creation of the empty file
*   - deletion of the database file
*   - metadatas display
*   - data import from csv files
*   - data export (test function)
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "db_file.h"
#include "table/country.h"
#include "system.h"
#include "utils.h"

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
        const struct table_metadata *table = &tables_metadatas[i];

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
        const struct table_metadata *table = &tables_metadatas[i];

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
        log_info(db, "Delete database", "Database file successfully deleted");
        printf("Database file %s sucessfully deleted.\n", db->header.db_name);
        return 0;
    }
    log_error(db, "Deleting database file");
    perror("Error while deleting database file");
    return 1;
}

/****************************************************************************************
* Imports dats from csv files to dat file
* returns 0 if all tables have been successfully updated
****************************************************************************************/
int import(struct db *db) {
    enum table i;                       // table index
    FILE *csv_file;                     // csv file pointer
    const unsigned buf_len = 1024;      // line buffer length
    char line[buf_len];                 // csv line
    int tab_error_count = 0, rec_count = 0; // count of tables updated and new records

    // reopen database file in write mode
    close_db(db);
    open_db(db, APPEND);

    for (i = 0; i < TAB_COUNT; i++) {
        const struct table_metadata *table = &tables_metadatas[i];
        char log_msg[64];
        
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
            rec_count += (*table->import)(db, line, buf_len);
        }

        // close the csv file
        fclose(csv_file);

        // log info
        sprintf(log_msg, "Table %-10s %10d new records", table->display_name, rec_count);
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
* Opens the database in a defined mode
* if it's opened in read mode, gets the metadata and fills the buffers
****************************************************************************************/
int open_db(struct db *db, enum opening_mode mode) {
    char log_msg[64];

    switch (mode) {
        case READ:
            strcpy(log_msg, "Opening database file in read mode");
            if ((db->dat_file = fopen(db->dat_file_path, "rb")) != NULL) {
                // Get the header from the database file
                fseek(db->dat_file, 0, SEEK_SET);
                fread(&db->header, sizeof(struct header), 1, db->dat_file);

                // TODO -> fill the buffers
            }
            break;

        case WRITE:
            strcpy(log_msg, "Opening database file in write mode");
            db->dat_file = fopen(db->dat_file_path, "wb");
            break;

        case APPEND:
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
* Displays the database metadatas (db name, number of reserved locations,
* number of records in each tables, etc.)
****************************************************************************************/
int display_metadatas(struct db *db) {
    enum table i;
    
    if (db->dat_file == NULL) {
        printf("Impossible : no database file opended.\n");
        log_info(db, "Display metadatas", "impossible to show metadatas (no file opened)");
        return 1;
    }

    printf("Database name: %s\n", db->header.db_name);
    printf("Database size: %d\n", db->header.size);
    puts("");

    for (i = 0; i < TAB_COUNT; i++) {
        printf("%s table:\n", tables_metadatas[i].display_name);
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
