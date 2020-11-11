/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Catalog :
*   - tables metadatas assignation
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include "catalog.h"
#include "table/country.h"

#include "system.h"

/***************************************************************************************
* Tables metadatas:
*   - name to write in the database file
*   - name to display to the user
*   - number of reserved locations (size of each table)
*   - tuple size
****************************************************************************************/
const struct table_metadata tables_metadatas[TAB_COUNT] = {
    {
        .prefix = "CTR",
        .display_name = "Country",
        .csv_path = CSV_DIR DIR_SEP"DB_Country.csv",
        .n_reserved = N_RES_CTR,
        .size = sizeof(struct country),
        .import = &import_country
    },
    {
        .prefix = "JOB",
        .display_name = "Job",
        .csv_path = CSV_DIR DIR_SEP"DB_Job.csv",
        .n_reserved = N_RES_JOB,
        .size = sizeof(struct job)
    },
    {
        .prefix = "IND",
        .display_name = "Industry",
        .csv_path = CSV_DIR DIR_SEP"DB_Industry.csv",
        .n_reserved = N_RES_IND,
        .size = sizeof(struct industry)
    },
    {
        .prefix = "GRP",
        .display_name = "Group",
        .csv_path = CSV_DIR DIR_SEP"DB_Group.csv",
        .n_reserved = N_RES_GRP,
        .size = sizeof(struct group)
    },
    {
        .prefix = "CMP",
        .display_name = "Company",
        .csv_path = CSV_DIR DIR_SEP"DB_Company.csv",
        .n_reserved = N_RES_CMP,
        .size = sizeof(struct company)
    },
    {
        .prefix = "PRS",
        .display_name = "Person",
        .csv_path = CSV_DIR DIR_SEP"DB_Person.csv",
        .n_reserved = N_RES_PRS,
        .size = sizeof(struct person)
    },
};
