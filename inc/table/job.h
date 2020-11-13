#pragma once
/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Job table functions prototypes
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include "database.h"

/***************************************************************************************
* Job table manipulation functions
****************************************************************************************/
// import a job from the csv file to the dat file
int import_job(struct db *db, char *csv_line);
int export_job(struct db *db);  // export a job from the dat file to the csv file
int load_job(struct db *db);    // load a job from the dat file to the buffer
int print_job(struct db *db);   // print a job on the stdout
