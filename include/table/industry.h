#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Industry table functions prototypes
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
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
 * Reads an industry by direct access in the database file
 * /!\ free after use
 *
 * @param db: database information stored in RAM
 * @param db: industry offset in the database file
 *
 * @return either
 *      a pointer to the industry found
 *      NULL if an error occured
 */
void *read_industry(struct db *db, unsigned offset);

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
 * Compares a searched id with the industry id
 *
 * @param db: database information stored in RAM
 * @param offset: offset of the industry to compare
 * @param searched: id searched
 *
 * @return either
 *      < 0 if the searched id is lower than the industry id
 *      0 if the searched id is equal to the industry id
 *      > 0 if the searched id is greater than the industry id
 *      INT_MAX if an error occured
 */
int compare_industry_id(struct db *db, unsigned offset, unsigned searched);

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
