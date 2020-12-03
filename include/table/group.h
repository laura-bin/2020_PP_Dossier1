#pragma once
/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Group table functions prototypes
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include "database.h"

/***************************************************************************************
* Group table manipulation functions
****************************************************************************************/
// import a group from the csv file to the dat file
int import_group(struct db *db, char *csv_line);
int export_group(struct db *db);    // export a group from the dat file to the csv file

/**
 * Loads the group table from the database file to the RAM stored buffer
 * 
 * @param db: database information stored in RAM
 * @param count: number of records to load
 *
 * @return the number of records suceessfully loaded
 */
int load_groups(struct db *db, int count);

int print_group(struct db *db);     // print a group on the stdout
