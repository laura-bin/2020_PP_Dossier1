#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 * 
 * Utils:
 *  - get a tuple by id
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/catalog.h"
#include "db_file/database.h"

/**
 * Gets one tuple by id, given or entered by the user
 * (binary search in the table buffers)
 * If no tuple is found, returns the nearest result found.
 * 
 * @param db: database file information stored in RAM
 * @param table: table in which search the tuple
 * @param out_searched: id searched, 0 if the id must be asked to the user
 * 
 * @return either
 *      the tuple found
 *      the nearest tuple found
 *      NULL if an error occured
 */
void *get_one_by_id(struct db *db, enum table table, unsigned *out_searched);
