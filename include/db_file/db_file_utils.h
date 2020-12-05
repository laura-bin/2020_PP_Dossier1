#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database file utils:
 *  - open database file
 *  - close database file
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "database.h"

/* File opening modes */
enum opening_mode {
    READ,
    WRITE,
    APPEND
};

/**
 * Closes the database file if a database file is opened
 * 
 * @param db: database information stored in RAM
 * 
 * @return either:
 *      0 if the database file has been closed
 *      1 if no database file was opened
 */
int close_db(struct db *db);

/**
 * Opens the database in a defined mode
 * if the database is opened in READ or in APPEND mode,
 * the database metadata and buffers are automatically filled.
 * 
 * Warning: in WRITE mode, if a dat file already exits, it is trucated
 * 
 * @param db: database information stored in RAM
 * @param mode: opening mode
 * 
 * @return either:
 *      0 if the database file has successfully been opened
 *     -1 if an error occured
 */
int open_db(struct db *db, enum opening_mode mode);