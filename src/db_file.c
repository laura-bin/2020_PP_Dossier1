/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Database acces :
*   - creation of the empty file
*   - deletion of the database file
*   - TODO metadatas display
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
    if (db->dat_file != NULL) fclose(db->dat_file);

    // then reopen database file in write mode (file is truncated)
    if ((db->dat_file = fopen(db->path, "wb")) == NULL) {
        log_error(db, "Database file creation");
    } else

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

    // reopen database in read mode
    fclose(db->dat_file);
    if ((db->dat_file = fopen(db->path, "rb")) == NULL) {
        log_error(db, "Database file creation");
    } else

    log_info(db, "Database file creation", "File successfully created");

    return 0;
}

/****************************************************************************************
* Deletes the database file
****************************************************************************************/
int delete_db(database *db) {
    FILE *fp;

    fp = fopen("test.dat", "wb");
    fclose(fp);
//    if (remove("test.dat") == 0) printf("OK");

    
    return 0;
}

int dummy_fct(database *db) {
    puts("dummy fct");
    pause_page();
    return 0;
}
