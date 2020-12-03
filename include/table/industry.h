#pragma once
/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Industry table functions prototypes
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include "database.h"

/***************************************************************************************
* Industry table manipulation functions
****************************************************************************************/
// import a industry from the csv file to the dat file
int import_industry(struct db *db, char *csv_line);
int export_industry(struct db *db); // export an industry from the dat file to the csv file

/**
 * Loads the industry table from the database file to the RAM stored buffer
 * 
 * @param db: database information stored in RAM
 * @param count: number of records to load
 *
 * @return the number of records suceessfully loaded
 */
int load_industries(struct db *db, int count);

int print_industry(struct db *db);  // print a industry on the stdout
