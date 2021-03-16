#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Company table functions prototypes
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

/**
 * Imports a company from a csv file line to the dat file
 *
 * @param db: database information stored in RAM
 * @param csv_line: csv line buffer to import
 *
 * @return the number of new records imported (1 if all is ok)
 */
int import_company(struct db *db, char *csv_line);

/**
 * Exports a company from the dat file to a new csv file
 *
 * @param db: database information stored in RAM
 *
 * @return the number of tuples successfully exported (1 or 0)
 */
int export_company(struct db *db);

/**
 * Reads the group id of a company
 *
 * @param db: database information stored in RAM
 * @param db: company offset in the database file
 *
 * @return either
 *      the id found
 *      UINT_MAX if an error occured
 */
unsigned read_company_group_id(struct db *db, unsigned offset);

/**
 * Reads a company by direct access in the database file
 * /!\ free after use
 *
 * @param db: database information stored in RAM
 * @param db: company offset in the database file
 *
 * @return either
 *      a pointer to the company found
 *      NULL if an error occured
 */
void *read_company(struct db *db, unsigned offset);

/**
 * Prints a detailed vue of a company
 *
 * @param company: company to print
 */
void print_company_details(struct company *company);

/**
 * Compares a searched id with the company id
 *
 * @param db: database information stored in RAM
 * @param offset: offset of the company to compare
 * @param searched: id searched
 *
 * @return either
 *      < 0 if the searched id is lower than the company id
 *      0 if the searched id is equal to the company id
 *      > 0 if the searched id is greater than the company id
 *      INT_MAX if an error occured
 */
int compare_company_id(struct db *db, unsigned offset, unsigned searched);

/**
 * Compares 2 companies country ids
 *
 * @param company1: first company compared
 * @param company2: second company compared
 *
 * @return either
 *      < 0 if the company1 country id is lower than the company2 country id
 *      0 if the company1 country id equals the company2 country id
 *      > 0 if the company1 country id is greater than the company2 country id
 */
int compare_company_country_id(const void *company1, const void *company2);
