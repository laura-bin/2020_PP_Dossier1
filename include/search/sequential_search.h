#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Generic sequential search
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"
#include "search/search_result.h"

/**
 * Searches records in the RAM stored buffer (sequential search)
 *
 * @param db: database information stored in RAM
 * @param tab: table type
 * @param searched: substring searched
 *
 * @return the list of results
 */
struct search_result sequential_search(struct db *db, enum table tab, char *searched);
