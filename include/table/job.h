#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Job table functions prototypes
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

/**
 * Imports a job from a csv file line to the dat file
 *
 * @param db: database information stored in RAM
 * @param csv_line: csv line buffer to import
 *
 * @return the number of new records imported (1 if all is ok)
 */
int import_job(struct db *db, char *csv_line);

/**
 * Exports a job from the dat file to a new csv file
 *
 * @param db: database information stored in RAM
 *
 * @return the number of tuples successfully exported (1 or 0)
 */
int export_job(struct db *db);

/**
 * Loads the job table from the database file to the RAM stored buffer
 *
 * @param db: database information stored in RAM
 * @param count: number of records to load
 *
 * @return the number of records suceessfully loaded
 */
int load_jobs(struct db *db, int count);

/**
 * Prints a job
 *
 * @param job: job to print
 */
void print_job(struct job *job);

/**
 * Prints the job table header containing its fields names
 */
void print_job_header(void);

/**
 * Compares a job referenced by its index with a searched substring
 *
 * @param db: database information stored in RAM
 * @param i: index of the job to compare
 * @param searched: substring searched
 *
 * @return either:
 *          - the pointer of the job if one of its field contains the substring
 *          - NULL if no field contains the substring
 */
void *compare_job(struct db *db, unsigned i, char *searched);
