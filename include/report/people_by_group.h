#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 * 
 * Report group employees grouped by company (main/detail report)
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

