#pragma once
//TODO
/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Job table functions prototypes
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include "db_file/database.h"

/***************************************************************************************
* Job table manipulation functions
****************************************************************************************/
// import a job from the csv file to the dat file
int import_job(struct db *db, char *csv_line);
int export_job(struct db *db);  // export a job from the dat file to the csv file

/**
 * Loads the job table from the database file to the RAM stored buffer
 * 
 * @param db: database information stored in RAM
 * @param count: number of records to load
 *
 * @return the number of records suceessfully loaded
 */
int load_jobs(struct db *db, int count);

int print_job(struct db *db);   // print a job on the stdout
