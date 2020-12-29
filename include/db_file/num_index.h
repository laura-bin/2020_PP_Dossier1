#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database numeric indexes creation:
 *  - create person by company id index
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
 *      0 if the index has successfully been created
 *     -1 if an error occured (errno is set)
 */
int create_person_by_company_id(struct db *db);
