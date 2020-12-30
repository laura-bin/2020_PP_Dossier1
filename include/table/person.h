#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Person table functions prototypes
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

/**
 * Imports a person from a csv file line to the dat file
 *
 * @param db: database information stored in RAM
 * @param csv_line: csv line buffer to import
 *
 * @return the number of new records imported (1 if all is ok)
 */
int import_person(struct db *db, char *csv_line);

/**
 * Exports a person from the dat file to a new csv file
 *
 * @param db: database information stored in RAM
 *
 * @return the number of tuples successfully exported (1 or 0)
 */
int export_person(struct db *db);

/**
 * Reads a person by direct access in the database file
 * /!\ free after use
 *
 * @param db: database information stored in RAM
 * @param db: person offset in the database file
 *
 * @return either
 *      a pointer to the person found
 *      NULL if an error occured
 */
void *read_person(struct db *db, unsigned offset);

/**
 * Prints a person
 *
 * @param person: person to print
 */
void print_person(struct person *person);

/**
 * Prints the person table header containing its fields names
 */
void print_person_header(void);
