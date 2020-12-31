#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database file binary searches on tables ids:
 *  - search company by id
 *  - search person by id
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

/**
 * Searches a group by its id
 * and shows the group found details or the 3 nearest results
 */
int search_group_by_id(struct db *db);

/**
 * Searches a company by its id
 * and shows the company found details or the 3 nearest results
 */
int search_company_by_id(struct db *db);

/**
 * Searches a person by its id
 * and shows the person found details or the 3 nearest results
 */
int search_person_by_id(struct db *db);
