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
// export an industry from the dat file to the csv file
int export_industry(struct db *db);  
int load_industry(struct db *db);    // load a industry from the dat file to the buffer
int print_industry(struct db *db);   // print a industry on the stdout
