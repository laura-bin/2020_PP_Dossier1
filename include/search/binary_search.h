#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Generic binary search
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <limits.h>

#include "db_file/database.h"

/**
 * Finds the offset of a record matching with a searched id
 * or the nearest result offset
 *
 * @param db: database information stored in RAM
 * @param searched: id searched
 * @param start: start index (0 on the first call)
 * @param stop: stop index (number of recorded indexes -1 on the first call)
 * @param table_type: table
 *
 * @return either
 *      the offset of the record found or of the nearest result
 *      UINTMAX if an error occured
 */
unsigned binary_search(struct db *db, int searched, int start, int stop,
                            enum table table_type);