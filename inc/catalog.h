#pragma once
/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Catalog :
*   - types & count of the different tables
*   - number of tuples reserved for each table
*   - database metadatas structure
*   - database tables structures
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include <stddef.h>

/***************************************************************************************
* Types of tables & table count
****************************************************************************************/
typedef enum {
    COUNTRY,
    JOB,
    INDUSTRY,
    GROUP,
    COMPANY,
    PERSON,
    TAB_COUNT   // number of tables in the database
} table_code;

/***************************************************************************************
* Number of reserved locations in the DB file for each type of tuple
****************************************************************************************/
#define N_RES_CTR 100
#define N_RES_JOB 200
#define N_RES_IND 100
#define N_RES_GRP 3000
#define N_RES_CMP 100000
#define N_RES_PRS 500000

/***************************************************************************************
* Table metadatas
****************************************************************************************/
struct table_metadata {
    char name[8];           // tuple prefix in the database
    char display_name[32];  // name displayed to the user
    unsigned n_reserved;    // number of tuples reserved in the table
    size_t size;            // tuple size
};

/***************************************************************************************
* Array of tables metadatas
****************************************************************************************/
extern const struct table_metadata tables_metadatas[TAB_COUNT];

/***************************************************************************************
* Tables common fields
****************************************************************************************/
struct table {
    table_code type;
    unsigned id;
};

/***************************************************************************************
* Country tuple
****************************************************************************************/
struct country {
    table_code type;
    unsigned id;            // pk
    char name[26];
    char zone[26];
    char iso[4];
};

/***************************************************************************************
* Job tuple
****************************************************************************************/
struct job{
    table_code type;
    unsigned id;            // pk
    char level[32];
    char department[32];
    char name[56];
};

/***************************************************************************************
* Industry tuple
****************************************************************************************/
struct industry {
    table_code type;
    unsigned id;            // pk
    char sector[32];
    char name[56];
};

/***************************************************************************************
* Group tuple
****************************************************************************************/
struct group {
    table_code type;
    unsigned id;            // pk
    char name[52];
    unsigned country_id;    // fk
};

/***************************************************************************************
* Company tuple
****************************************************************************************/
struct company {
    table_code type;
    unsigned id;            // pk
    unsigned id_group;      // fk
    unsigned id_country;    // fk
    unsigned id_industry;   // fk
    char name[76];
};

/***************************************************************************************
* Person tuple
****************************************************************************************/
struct person {
    table_code type;
    unsigned id;            // pk
    unsigned id_company;    // fk
    unsigned id_job;        // fk
    char title[16]; 
    char firstname[32];
    char lastname[32];
    char gender[8];
    char creation_date[12]; //struct tm creation_date; // date of creation of the record
    char phone_number[16];
    char mobile_number[16];
    char mail[40];
    unsigned shares;
};
