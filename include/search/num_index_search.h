#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Generic search by numeric index
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"
#include "search/search_result.h"

/**
 * Searches records by a given numeric index
 * and returns the list of results
 *
 * @param db: database information stored in RAM
 * @param type: numeric index type
 * @param searched: value serached
 * 
 * @return the list of results
 */
struct search_result search_by_num_index(struct db *db, enum num_index type, unsigned searched);
