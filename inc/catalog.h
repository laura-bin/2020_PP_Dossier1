#pragma once
/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Catalog :
*   - database tables structures
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/
#include <time.h>

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

struct table_metadata {
    char name[8];           // tuple prefix in the database
    unsigned n_reserved;    // number of tuples reserved in the table
    size_t size;            // tuple size
};

extern const struct table_metadata tables_metadatas[TAB_COUNT];

/***************************************************************************************
* Entities common fields
****************************************************************************************/
typedef struct {
    table_code type;
    unsigned id;
} entity;

/***************************************************************************************
* Country entity
****************************************************************************************/
typedef struct {
    table_code type;
    unsigned id;
    char name[26];
    char zone[26];
    char iso[4];
} country_entity;

/***************************************************************************************
* Job entity
****************************************************************************************/
typedef struct {
    table_code type;
    unsigned id;
    char level[32];
    char department[32];
    char name[56];
} job_entity;

/***************************************************************************************
* Industry entity
****************************************************************************************/
typedef struct {
    table_code type;
    unsigned id;
    char sector[32];
    char name[56];
} industry_entity;

/***************************************************************************************
* Group entity
****************************************************************************************/
typedef struct {
    table_code type;
    unsigned id;
    char name[52];
    unsigned country_id;    // foreign key
} group_entity;

/***************************************************************************************
* Company entity
****************************************************************************************/
typedef struct {
    table_code type;
    unsigned id;
    unsigned id_group;
    unsigned id_country;
    unsigned id_industry;
    char name[76];
} company_entity;

/***************************************************************************************
* Person entity
****************************************************************************************/
typedef struct {
    table_code type;
    unsigned id;
    unsigned id_company;
    unsigned id_job;
    char title[16]; 
    char firstname[32];
    char lastname[32];
    char gender[8];
    struct tm creation_date;  // date of recording -> 12 TODO -> char
    char phone_number[16];
    char mobile_number[16];
    char mail[40];
    unsigned shares;
} person_entity;
