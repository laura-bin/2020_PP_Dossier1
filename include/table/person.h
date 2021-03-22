#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Person table functions prototypes
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
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
 * Reads the company id of a person
 *
 * @param db: database information stored in RAM
 * @param db: person offset in the database file
 *
 * @return either
 *      the id found
 *      UINT_MAX if an error occured
 */
unsigned read_person_company_id(struct db *db, unsigned offset);

/**
 * Reads the lastname of a person
 *
 * @param db: database information stored in RAM
 * @param db: person offset in the database file
 * @param lastname: lastname returned
 */
void read_person_lastname(struct db *db, unsigned offset, char *out_lastname);

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
 * Prints a detailed vue of a person
 *
 * @param person: person to print
 */
void print_person_details(struct person *person);

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

/**
 * Compares a searched id with the person id
 *
 * @param db: database information stored in RAM
 * @param offset: offset of the person to compare
 * @param searched: id searched
 *
 * @return either
 *      < 0 if the searched id is lower than the person id
 *      0 if the searched id is equal to the person id
 *      > 0 if the searched id is greater than the person id
 *      INT_MAX if an error occured
 */
int compare_person_id(struct db *db, unsigned offset, unsigned searched);

/**
 * Compares 2 peole lastnames
 *
 * @param person1: first person compared
 * @param person2: second person compared
 *
 * @return either
 *      < 0 if the person1 lastname is before the person2 lastname in alhabetical order
 *      0 if the person1 lastname is the same as the person2 lastname
 *      > 0 if the person1 lastname is after the person2 lastname in alhabetical order
 */
int compare_person_lastname(const void *person1, const void *person2);
