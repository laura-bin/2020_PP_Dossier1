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

/**
 * Create the report of the sum of shares owned by the employees of a group
 * with statistics by job level and gender
 * 
 * @param db: database information stored in RAM
 */
struct people_shares_data {
    char job_level[JOB_LEVEL_LEN];  // job level name
    double shares_sum_f;            // total value of shares held by female employees
    double shares_sum_m;            // total value of shares held by male employees
    double shares_sum_x;            // total value of shares held by non binary employees
};

int report_people_shares_sum_group_by_job_level_group_by_gender(struct db *db);
