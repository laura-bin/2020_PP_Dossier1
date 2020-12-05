#pragma once
//TODO
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Company table functions prototypes
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "database.h"

/***************************************************************************************
* Company table manipulation functions
****************************************************************************************/
// import a company from the csv file to the dat file
int import_company(struct db *db, char *csv_line);
int export_company(struct db *db);  // export a company from the dat file to the csv file
int print_company(struct db *db);   // print a company on the stdout
