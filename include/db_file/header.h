#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database header creation
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <sys/types.h>

#include "db_file/database.h"

/**
 * Creates the database file header
 * 
 * @param db: database information stored in RAM
 *
 * @return either:
 *      the max entity size
 *     -1 if an error occured (errno is set)
 */
ssize_t create_header(struct db *db);
