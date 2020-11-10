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

/***************************************************************************************
* Tables metadatas:
*   - name to write in the database file
*   - name to display to the user
*   - number of reserved locations (size of each table)
*   - tuple size
****************************************************************************************/
const struct table_metadata tables_metadatas[TAB_COUNT] = {
    {
        .name = "CTR",
        .display_name = "Country",
        .n_reserved = N_RES_CTR,
        .size = sizeof(struct country)
    },
    {
        .name = "JOB",
        .display_name = "Job",
        .n_reserved = N_RES_JOB,
        .size = sizeof(struct job)
    },
    {
        .name = "IND",
        .display_name = "Industry",
        .n_reserved = N_RES_IND,
        .size = sizeof(struct industry)
    },
    {
        .name = "GRP",
        .display_name = "Group",
        .n_reserved = N_RES_GRP,
        .size = sizeof(struct group)
    },
    {
        .name = "CMP",
        .display_name = "Company",
        .n_reserved = N_RES_CMP,
        .size = sizeof(struct company)
    },
    {
        .name = "PRS",
        .display_name = "Person",
        .n_reserved = N_RES_PRS,
        .size = sizeof(struct person)
    },
};
