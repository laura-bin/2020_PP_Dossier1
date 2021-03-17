#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Report employees share value sum grouped by gender and by job (aggregation report)
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

int report_people_shares_sum_group_by_gender_group_by_job(struct db *db);
