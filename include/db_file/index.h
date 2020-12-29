#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database indexes creation:
 *  - create person by company id index
 *  - create person by lastname index
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

/**
 * Creates the person by company id index
 * and writes it in the database file
 * 
 * @param db: database information stored in RAM
 * 
 * @return either
 *      0 if the header has successfully benn created
 *     -1 if an error occured (errno is set)
 */
int create_person_by_company_id(struct db *db);

/**
 * Creates the person by lastname index
 * and writes it in the database file
 * 
 * @param db: database information stored in RAM
 * 
 * @return either
 *      0 if the header has successfully benn created
 *     -1 if an error occured (errno is set)
 */
int create_person_by_lastname(struct db *db);