#pragma once
/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Country table functions prototypes
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include "database.h"

/***************************************************************************************
* Country table manipulation functions
****************************************************************************************/
// import a country from the csv file to the dat file
int import_country(struct db *db, char *csv_line);
int export_country(struct db *db);  // export a country from the dat file to the csv files
int load_country(struct db *db);    // load a country from the dat file to the buffer
int print_country(struct db *db);   // print a country on the stdout
