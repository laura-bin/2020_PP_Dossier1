#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Industry table functions prototypes
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

/**
 * Imports a industry from a csv file line to the dat file
 *
 * @param db: database information stored in RAM
 * @param csv_line: csv line buffer to import
 *
 * @return the number of new records imported (1 if all is ok)
 */
int import_industry(struct db *db, char *csv_line);

/**
 * Exports a industry from the dat file to a new csv file
 *
 * @param db: database information stored in RAM
 *
 * @return the number of tuples successfully exported (1 or 0)
 */
int export_industry(struct db *db);

/**
 * Loads the industry table from the database file to the RAM stored buffer
 *
 * @param db: database information stored in RAM
 * @param count: number of records to load
 *
 * @return the number of records suceessfully loaded
 */
int load_industries(struct db *db, int count);

/**
 * Prints an industry
 *
 * @param industry: industry to print
 */
void print_industry(struct industry *industry);

/**
 * Prints the industry table header containing its fields names
 */
void print_industry_header(void);

/**
 * Compares an industry referenced by its index with a searched substring
 *
 * @param db: database information stored in RAM
 * @param i: index of the industry to compare
 * @param searched: substring searched
 *
 * @return either:
 *          - the pointer of the industry if one of its field contains the substring
 *          - NULL if no field contains the substring
 */
void *compare_industry(struct db *db, unsigned i, char *searched);
