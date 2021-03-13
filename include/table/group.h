#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Group table functions prototypes
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

/**
 * Imports a group from a csv file line to the dat file
 *
 * @param db: database information stored in RAM
 * @param csv_line: csv line buffer to import
 *
 * @return the number of new records imported (1 if all is ok)
 */
int import_group(struct db *db, char *csv_line);

/**
 * Exports a group from the dat file to a new csv file
 *
 * @param db: database information stored in RAM
 *
 * @return the number of tuples successfully exported (1 or 0)
 */
int export_group(struct db *db);

/**
 * Loads the group table from the database file to the RAM stored buffer
 *
 * @param db: database information stored in RAM
 * @param count: number of records to load
 *
 * @return the number of records suceessfully loaded
 */
int load_groups(struct db *db, int count);

/**
 * Reads a group by direct access in the database file
 * /!\ free after use
 *
 * @param db: database information stored in RAM
 * @param db: group offset in the database file
 *
 * @return either
 *      a pointer to the group found
 *      NULL if an error occured
 */
void *read_group(struct db *db, unsigned offset);

/**
 * Prints a detailed vue of a group
 *
 * @param group: group to print
 */
void print_group_details(struct group *group);

/**
 * Prints a group
 *
 * @param group: group to print
 */
void print_group(struct group *group);

/**
 * Prints the group table header containing its fields names
 */
void print_group_header(void);

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
int compare_group_id(struct db *db, unsigned offset, unsigned searched);

/**
 * Compares a group referenced by its index with a searched substring
 *
 * @param db: database information stored in RAM
 * @param i: index of the group to compare
 * @param searched: substring searched
 *
 * @return either:
 *          - the pointer of the group if one of its field contains the substring
 *          - NULL if no field contains the substring
 */
void *compare_group(struct db *db, unsigned i, char *searched);
