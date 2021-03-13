#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database file binary searches on tables ids displayed on the standard output:
 *  - search group by id
 *  - search company by id
 *  - search person by id
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

/**
 * Displays the group using id binary search
 * (shows the group found details or the 3 nearest results)
 */
int search_group_by_id(struct db *db);

/**
 * Displays the company using id binary search
 * (shows the company found details or the 3 nearest results)
 */
int search_company_by_id(struct db *db);

/**
 * Displays the person using id binary search
 * (shows the person found details or the 3 nearest results)
 */
int search_person_by_id(struct db *db);
