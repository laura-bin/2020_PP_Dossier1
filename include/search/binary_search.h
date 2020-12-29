#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database file binary searche:
 *  - search company by id
 *  - search person by id
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

/**
 * Searches a company by its id
 * 
 * @return either
 *      if the company have benn found: the person found
 *      else: the closest results
 */
void *search_company_by_id(struct db *db);

/**
 * Searches a person by its id
 * 
 * @return either
 *      if the person have benn found: the person found
 *      else: the closest results
 */
void *search_person_by_id(struct db *db);
