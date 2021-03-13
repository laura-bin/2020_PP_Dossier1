#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database file searches by numeric index displayed on the standard output:
 *  - search people by company id
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

/**
 * Displays the people using company id search
 *
 * @param db: database information stored in RAM
 */
int search_people_by_company_id(struct db *db);
