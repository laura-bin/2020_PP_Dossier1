#pragma once
//TODO
/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Country table manipulation functions prototypes
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include "database.h"

/**
 * Imports a country from the csv file to the dat file
 * 
 * @param db: database information stored in RAM
 * @param service: port number or service
 *
 * @return the number of elements suceessfully imported/
 *          1 if the import was sucessfull
 *          0 if an error occured
 */
int import_country(struct db *db, char *csv_line);



int export_country(struct db *db);  // export a country from the dat file to the csv files

/**
 * Loads the country table from the database file to the RAM stored buffer
 * 
 * @param db: database information stored in RAM
 * @param count: number of records to load
 *
 * @return the number of records suceessfully loaded
 */
int load_countries(struct db *db, int count);



int print_country(struct db *db);   // print a country on the stdout
