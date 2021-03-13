#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database header creation
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

/**
 * Creates the database file header
 * 
 * @param db: database information stored in RAM
 *
 * @return either:
 *      0 if the header have successfully been written in the database file
 *     -1 if an error occured (errno is set)
 */
int create_header(struct db *db);
