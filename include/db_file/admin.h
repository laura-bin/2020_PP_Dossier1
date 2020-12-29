#pragma once
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

#include "database.h"

/**
 * Creates an empty database file (.dat)
 * 
 * @param db: database information stored in RAM
 *
 * @return either:
 *      0 if the database file has successfully been created
 *     -1 if an error occured
 */
int create_db(struct db *db);

/**
 * Deletes the database file
 * 
 * @param db: database information stored in RAM
 *
 * @return either:
 *      0 if the database file has successfully been deleted
 *     -1 if an error occured
 */
int delete_db(struct db *db);

/**
 * Imports data from csv files to dat file
 * then creates the indexes
 * 
 * @param db: database information stored in RAM
 *
 * @return either:
 *      0 if all the data has successfully been imported
 *     -1 if no database file is available
 *     the number of tables on which an error occured
 */
int import(struct db *db);

/**
 * Exports data from dat file to csv files
 * 
 * @param db: database information stored in RAM
 *
 * @return either:
 *      0 if all table has successfully been exported
 *     -1 if no database file is available
 *     the number of tables on which an error occured
 */
int export(struct db *db);

/**
 * Displays the database metadata (db name, number of reserved locations,
 * number of records in each tables, etc.)
 * 
 * @param db: database information stored in RAM
 *
 * @return either:
 *      0 if the function has successfully been executed
 *     -1 if no database file is available
 */
int display_metadata(struct db *db);
