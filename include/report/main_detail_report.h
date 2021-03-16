/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 * 
 * Main/detail reports:
 *  - group employees grouped by company
 *  - group companies grouped by country
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

/**
 * Create the report of a given group employees ordered by company
 * 
 * @param db: database information stored in RAM
 */
int report_people_by_group_order_by_company(struct db *db);

/**
 * Create the report of a given group companies ordered by countries
 * 
 * @param db: database information stored in RAM
 */
int report_companies_by_group_order_by_country(struct db *db);
