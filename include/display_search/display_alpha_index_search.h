#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Searches by alphanumeric index displayed on the standard output:
 *  - search people by lastname prefix
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

/**
 * Displays the people using lastname prefix search
 *
 * @param db: database information stored in RAM
 */
int search_people_by_lastname(struct db *db);
