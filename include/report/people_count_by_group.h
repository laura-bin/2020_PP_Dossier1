#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Report group employees count grouped by companies:
 *  group employees and employees known in the database (aggregation report)
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

int report_people_count_by_group(struct db *db);
