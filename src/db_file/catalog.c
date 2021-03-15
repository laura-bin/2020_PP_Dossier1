/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Catalog :
 *  - tables metadata assignation
 *  - indexes metadata assignation
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "table/country.h"
#include "table/job.h"
#include "table/industry.h"
#include "table/group.h"
#include "table/company.h"
#include "table/person.h"
#include "utils/system.h"

/* Tables metadata assignation */
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
        .compare = &compare_country,
        .compare_id = &compare_country_id,
        .read = NULL,
        .print = (void (*)(void *))&print_country,
        .print_details = NULL,
        .print_header = &print_country_header
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
        .compare = &compare_job,
        .compare_id = NULL,
        .read = NULL,
        .print = (void (*)(void *))&print_job,
        .print_details = NULL,
        .print_header = &print_job_header
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
        .compare = &compare_industry,
        .compare_id = NULL,
        .read = NULL,
        .print = (void (*)(void *))&print_industry,
        .print_details = NULL,
        .print_header = &print_industry_header
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
        .compare = &compare_group,
        .compare_id = &compare_group_id,
        .read = &read_group,
        .print = (void (*)(void *))&print_group,
        .print_details = (void (*)(void *))&print_group_details,
        .print_header = &print_group_header
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
        .compare = NULL,
        .compare_id = &compare_company_id,
        .read = &read_company,
        .print = NULL,
        .print_details = (void (*)(void *))&print_company_details,
        .print_header = NULL
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
        .compare = NULL,
        .compare_id = &compare_person_id,
        .read = &read_person,
        .print = (void (*)(void *))&print_person,
        .print_details = (void (*)(void *))&print_person_details,
        .print_header = &print_person_header
    }
};

/* Numeric indexes metadata assignation */
const struct num_index_metadata num_indexes_metadata[NUM_INDEX_COUNT] = {
    {
        .prefix = "CMP_GRP",
        .table = COMPANY,
        .read_value = &read_company_group_id
    },
    {
        .prefix = "PRS_CMP",
        .table = PERSON,
        .read_value = &read_person_company_id
    }
};

/* Alphanumeric indexes metadata assignation */
const struct alpha_index_metadata alpha_indexes_metadata[ALPHA_INDEX_COUNT] = {
    {
        .prefix = "PRS_LN",
        .table = PERSON,
        .read_value = &read_person_lastname
    }
};
