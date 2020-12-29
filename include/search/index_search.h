#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database file searches by index:
 *  - search people by company id
 *  - search people by lastname prefix
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

/**
 * Searches people by their company id
 */
int search_people_by_company_id(struct db *db);

/**
 * Searches people by lastname prefix
 */
int search_people_by_lastname(struct db *db);
