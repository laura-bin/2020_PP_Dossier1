/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database file utils:
 *  - open database file
 *  - close database file
 * 
 * Private function:
 *  - load header in RAM
 *  - load code tables in RAM
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <string.h>

#include "db_file/open_close.h"
#include "utils/logger.h"

/* PRIVATE FUNCTIONS */

/**
 * Loads the dat file header in RAM stored database information
 * If no dat file is opened, this function does nothing
 * 
 * @param db: database information stored in RAM
 * 
 * @return either:
 *      0 if the method has successfully been executed or if the dat file pointer was NULL
 *     -1 if an error occured
 */
int load_header(struct db *db) {
    if (db->dat_file == NULL) return 0;

    fseek(db->dat_file, 0, SEEK_SET);
    if (fread(&db->header, sizeof(struct header), 1, db->dat_file) == 1) {
        log_info(db, "Loading header", "Success");
        return 0;
    }
    log_info(db, "Loading header", "Error");
    return -1;
}

/**
 * Loads in RAM tables for which a load method is defined (code tables)
 * 
 * @param db: database information stored in RAM
 * 
 * @return the count of tables sucessfully loaded
 */
int load_buffers(struct db *db) {
    enum table i;           // table iteration index
    int n_tab_loaded = 0;   // count of successfully loaded tables
    int n_rec_loaded = 0;   // count of successfully loaded records for each table
    int n_rec = 0;          // number of records to load for each table

    for (i = 0; i < TAB_COUNT; i++) {
        char log_from[64];
        char log_msg[64];
        const struct table_metadata *table = &tables_metadata[i];

        sprintf(log_from, "%s table load", table->display_name);

        if (table->load != NULL) {
            n_rec = db->header.n_rec_table[i];
            if (n_rec == 0) continue;

            fseek(db->dat_file, db->header.offset_table[i], SEEK_SET);
            n_rec_loaded = table->load(db, n_rec);
            if (n_rec == n_rec_loaded) {
                sprintf(log_msg, "%d records successfully loaded", n_rec_loaded);
                n_tab_loaded++;
            } else {
                sprintf(log_msg, "%d records loaded on %d", n_rec_loaded, n_rec);
            }
            log_info(db, log_from, log_msg);
        }
    }
    return n_tab_loaded;
}

/* HEADER IMPLEMENTATION */

int close_db(struct db *db) {
    if (db->dat_file == NULL) return 1;

    fclose(db->dat_file);
    db->dat_file = NULL;
    log_info(db, "Closing database file", "Success");
    return 0;
}

int open_db(struct db *db, enum opening_mode mode) {
    char log_msg[64];

    // close the dat file if it is already opened
    close_db(db);

    // (re)open the dat file
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

    // log info
    if (db->dat_file == NULL) {
        log_error(db, log_msg);
        return -1;
    }
    log_info(db, log_msg, "Success");

    // load the header & the table buffers
    if (mode != WRITE) {
        load_header(db);
        load_buffers(db);
    }

    return 0;
}