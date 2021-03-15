#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Country table manipulation functions prototypes
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

/**
 * Imports a country from a csv file line to the dat file
 *
 * @param db: database information stored in RAM
 * @param csv_line: csv line buffer to import
 *
 * @return the number of new records imported (1 if all is ok)
 */
int import_country(struct db *db, char *csv_line);

/**
 * Exports a country from the dat file to a new csv file
 *
 * @param db: database information stored in RAM
 *
 * @return the number of tuples successfully exported (1 or 0)
 */
int export_country(struct db *db);

/**
 * Loads the country table from the database file to the RAM stored buffer
 *
 * @param db: database information stored in RAM
 * @param count: number of records to load
 *
 * @return the number of records suceessfully loaded
 */
int load_countries(struct db *db, int count);

/**
 * Prints a country
 *
 * @param country: country to print
 */
void print_country(struct country *country);

/**
 * Prints the country table header containing its fields names
 */
void print_country_header(void);

/**
 * Compares a searched id with the group id
 *
 * @param db: database information stored in RAM
 * @param offset: offset of the group to compare
 * @param searched: id searched
 *
 * @return either
 *      < 0 if the searched id is lower than the group id
 *      0 if the searched id is equal to the group id
 *      > 0 if the searched id is greater than the group id
 *      INT_MAX if an error occured
 */
int compare_country_id(struct db *db, unsigned offset, unsigned searched);

/**
 * Compares a country referenced by its index with a searched substring
 *
 * @param db: database information stored in RAM
 * @param i: index of the country to compare
 * @param searched: substring searched
 *
 * @return either:
 *          - the pointer of the country if one of its field contains the substring
 *          - NULL if no field contains the substring
 */
void *compare_country(struct db *db, unsigned i, char *searched);
