#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Company table functions prototypes
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

/**
 * Imports a company from a csv file line to the dat file
 *
 * @param db: database information stored in RAM
 * @param csv_line: csv line buffer to import
 *
 * @return the number of new records imported (1 if all is ok)
 */
int import_company(struct db *db, char *csv_line);

/**
 * Exports a company from the dat file to a new csv file
 *
 * @param db: database information stored in RAM
 *
 * @return the number of tuples successfully exported (1 or 0)
 */
int export_company(struct db *db);

int print_company(struct db *db);   // print a company on the stdout
