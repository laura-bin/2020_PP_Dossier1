#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database alphanumeric indexes creation
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

/**
 * Creates the specified index and writes it to the database file
 *
 * 
 * @param db: database information stored in RAM
 * @param index_type: the index to create
 * 
 * @return either
 *      0 if the index has successfully been created
 *     -1 if an error occured (errno is set)
 */
int create_alpha_index(struct db *db, enum alpha_index index_type);
