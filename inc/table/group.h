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
// export a group from the dat file to the csv file
int export_group(struct db *db);
int load_group(struct db *db);    // load a group from the dat file to the buffer
int print_group(struct db *db);   // print a group on the stdout
