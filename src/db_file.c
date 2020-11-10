/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Database acces :
*   - creation of the empty file
*   - deletion of the database file
*   - metadatas display
*   - TODO import of data from csv files
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "db_file.h"
#include "system.h"
#include "utils.h"

/****************************************************************************************
* Creates an empty DB file (.dat)
****************************************************************************************/
int create_db(database *db) {
    table_code i;           // index used to create each table
    unsigned j = 0;         // index used to create each empty tuple
    size_t offset;          // offset of each entity (table/index)
    char *buffer;           // empty tuple buffer
    size_t max_size = 0;    // max entity size used to initialize the buffer

    log_info(db, "Database file creation", "Starting...");
    puts("Starting database file creation...\n");

    // close database file if a file is opened
    close_db(db);

    // then reopen database file in write mode (file is truncated)
    if ((db->dat_file = fopen(db->path, "wb")) == NULL) {
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
        strcpy(buffer, table->name);

        for (j = 0; j < table->n_reserved; j++) {
            fwrite(buffer, table->size, 1, db->dat_file);
        }
    }
    free(buffer);

    printf("Database %s sucessfully created\n", db->header.db_name);
    log_info(db, "Database file creation", "File successfully created");

    // reopen database in read mode
    close_db(db);
    open_db(db);

    return 0;
}

/****************************************************************************************
* Deletes the database file
****************************************************************************************/
int delete_db(database *db) {
    close_db(db);
    if (remove(db->path) == 0) {
        log_info(db, "Delete database", "Database file successfully deleted");
        printf("Database file %s sucessfully deleted.\n", db->filename);
        return 0;
    }
    log_error(db, "Deleting database file");
    perror("Error while deleting database file");
    return 1;
}

/****************************************************************************************
* Opens the database in read mode, gets the metadata and fills the buffers
****************************************************************************************/
int open_db(database *db) {
    if ((db->dat_file = fopen(db->path, "rb")) == NULL) {
        log_error(db, "Opening database file");
        return 1;
    }
    log_info(db, "Opening database file", "Database file opened in read mode");

    // Get the header from the database file
    fseek(db->dat_file, 0, SEEK_SET);
    fread(&db->header, 1, sizeof(struct header), db->dat_file);

    // TODO -> fill the buffers

    return 0;
}

/****************************************************************************************
* Closes the database file
****************************************************************************************/
int close_db(database *db) {
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
int display_metadatas(database *db) {
    table_code i;
    
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

int dummy_fct(database *db) {
    puts("dummy fct");
    pause_page();
    return 0;
}
