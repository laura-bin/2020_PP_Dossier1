#pragma once
//TODO
/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Person table functions prototypes
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include "db_file/database.h"

/***************************************************************************************
* Person table manipulation functions
****************************************************************************************/
// import a person from the csv file to the dat file
int import_person(struct db *db, char *csv_line);
int export_person(struct db *db);  // export a person from the dat file to the csv file
int print_person(struct db *db);   // print a person on the stdout
