/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Catalogue : definition des tables de la base de données
*
* Programmation procedurale 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include "catalog.h"

/***************************************************************************************
* Tables metadatas:
*   - name to write in the database file
*   - number of reserved locations (size of each table)
*   - tuple size
****************************************************************************************/
const struct table_metadata tables_metadatas[TAB_COUNT] = {
    {
        .name = "CTR",
        .n_reserved = N_RES_CTR,
        .size = sizeof(country_entity)
    },
    {
        .name = "JOB",
        .n_reserved = N_RES_JOB,
        .size = sizeof(job_entity)
    },
    {
        .name = "IND",
        .n_reserved = N_RES_IND,
        .size = sizeof(industry_entity)
    },
    {
        .name = "GRP",
        .n_reserved = N_RES_GRP,
        .size = sizeof(group_entity)
    },
    {
        .name = "CMP",
        .n_reserved = N_RES_CMP,
        .size = sizeof(company_entity)
    },
    {
        .name = "PRS",
        .n_reserved = N_RES_PRS,
        .size = sizeof(person_entity)
    },
};

