/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Catalog :
 *  - tables metadata assignation
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/catalog.h"
#include "table/country.h"
#include "table/job.h"
#include "table/industry.h"
#include "table/group.h"
#include "table/company.h"
#include "table/person.h"
#include "utils/system.h"

/**
 * Tables metadata:
 *  - prefix to write in the database file
 *  - name to display to the user
 *  - number of reserved locations (size of each table)
 *  - tuple size
 */
const struct table_metadata tables_metadata[TAB_COUNT] = {
    {
        .prefix = "CTR",
        .display_name = "Country",
        .csv_path = IMP_DIR DIR_SEP"DB_Country.csv",
        .csv_header = "Id;Nm_Cty;Nm_Zon;Cd_Iso",
        .n_reserved = N_RES_CTR,
        .size = sizeof(struct country),
        .import = &import_country,
        .export = &export_country,
        .load = &load_countries,
        .print_buf = &print_buf_countries,
        .print = NULL
    },
    {
        .prefix = "JOB",
        .display_name = "Job",
        .csv_path = IMP_DIR DIR_SEP"DB_Job.csv",
        .csv_header = "Id;Nm_Lev;Nm_Dep;Nm_Job",
        .n_reserved = N_RES_JOB,
        .size = sizeof(struct job),
        .import = &import_job,
        .export = &export_job,
        .load = &load_jobs,
        .print_buf = &print_buf_jobs,
        .print = NULL
    },
    {
        .prefix = "IND",
        .display_name = "Industry",
        .csv_path = IMP_DIR DIR_SEP"DB_Industry.csv",
        .csv_header = "Id;Nm_Sec;Nm_Ind",
        .n_reserved = N_RES_IND,
        .size = sizeof(struct industry),
        .import = &import_industry,
        .export = &export_industry,
        .load = &load_industries,
        .print_buf = &print_buf_industries,
        .print = NULL
    },
    {
        .prefix = "GRP",
        .display_name = "Group",
        .csv_path = IMP_DIR DIR_SEP"DB_Group.csv",
        .csv_header = "Id;Nm_Grp;Id_Cty",
        .n_reserved = N_RES_GRP,
        .size = sizeof(struct group),
        .import = &import_group,
        .export = &export_group,
        .load = &load_groups,
        .print_buf = &print_buf_groups,
        .print = NULL
    },
    {
        .prefix = "CMP",
        .display_name = "Company",
        .csv_path = IMP_DIR DIR_SEP"DB_Company.csv",
        .csv_header = "id;id_grp;id_cty;id_ind;nm_cpy;nm_adr;cd_pos;nm_cit;nr_tel;nm_www;dt_cre;nr_emp;am_val",
        .n_reserved = N_RES_CMP,
        .size = sizeof(struct company),
        .import = &import_company,
        .export = &export_company,
        .load = NULL,
        .print_buf = NULL,
        .print = NULL
    },
    {
        .prefix = "PRS",
        .display_name = "Person",
        .csv_path = IMP_DIR DIR_SEP"DB_Person.csv",
        .csv_header = "id;id_cpy;id_job;nm_civ;nm_fst;nm_lst;cd_sex;dt_cre;nr_tel;nr_gsm;nm_mail;nr_val",
        .n_reserved = N_RES_PRS,
        .size = sizeof(struct person),
        .import = &import_person,
        .export = &export_person,
        .load = NULL,
        .print_buf = NULL,
        .print = NULL
    },
};