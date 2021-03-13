#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Generic search by alphanumeric index
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"
#include "search/search_result.h"

/**
 * Searches records by a given alphanumeric index
 * and returns the list of results
 *
 * @param db: database information stored in RAM
 * @param type: alphanumeric index type
 * @param searched: string prefix searched into the index
 * 
 * @return the list of results
 */
struct search_result search_by_alpha_index(struct db *db, enum alpha_index type, char *searched);
