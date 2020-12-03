#pragma once
/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Catalog:
*   - tables infos : number of tuples reserved for each table, prefix length, etc.
*   - database metatada structure
*   - tuples definitions (structures written in the database file)
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include <stddef.h>

/***************************************************************************************
* Files paths & directories
****************************************************************************************/
#define DAT_DIR "data_clients"  // database file & log file directory
#define IMP_DIR "data_import"   // directory containing csv files used for import
#define EXP_DIR "data_export"   // directory containing csv files used for export
#define CSV_BUF_LEN 1024        // buffer length used on read/write csv files

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
* Size of tuple prefix corresponding to the table type (CTR, JOB, etc.)
****************************************************************************************/
#define PREF_LEN 8

/***************************************************************************************
* Types of tables & table count
****************************************************************************************/
enum table {
    COUNTRY,
    JOB,
    INDUSTRY,
    GROUP,
    COMPANY,
    PERSON,
    TAB_COUNT   // number of tables in the database
};

/***************************************************************************************
* Table metadata
****************************************************************************************/
struct db;
struct table_metadata {
    char prefix[PREF_LEN];  // tuple prefix in the database
    char display_name[32];  // name displayed to the user
    unsigned n_reserved;    // number of tuples reserved in the table
    size_t size;            // tuple size
    char csv_path[255];     // csv file path used to import data
    char csv_header[255];   // csv file header
    int (*import)(struct db *, char *);     // import function pointer
    int (*export)(struct db *);             // export function pointer
    int (*load)(struct db *, int count);    // load function pointer
    int (*print)(struct db *);              // print function pointer
};

/***************************************************************************************
* Array of tables metadata
****************************************************************************************/
extern const struct table_metadata tables_metadata[TAB_COUNT];

/***************************************************************************************
* Country tuple
****************************************************************************************/
struct country {
    char type[PREF_LEN];    // "CTR"
    unsigned id;            // pk
    char name[24];
    char zone[24];
    char iso[4];
};

/***************************************************************************************
* Job tuple
****************************************************************************************/
struct job {
    char type[PREF_LEN];    // "JOB"
    unsigned id;            // pk
    char level[22];
    char department[24];
    char name[38];
};

/***************************************************************************************
* Industry tuple
****************************************************************************************/
struct industry {
    char type[PREF_LEN];    // "IND"
    unsigned id;            // pk
    char sector[20];
    char name[32];
};

/***************************************************************************************
* Group tuple
****************************************************************************************/
struct group {
    char type[PREF_LEN];    // "GRP"
    unsigned id;            // pk
    char name[46];
    unsigned country_id;    // fk
};

/***************************************************************************************
* Company tuple
****************************************************************************************/
struct company {
    char type[PREF_LEN];    // "CMP"
    unsigned id;            // pk
    unsigned id_group;      // fk
    unsigned id_country;    // fk
    unsigned id_industry;   // fk
    char name[64];
    char address[64];
    char zip_code[16];
    char city[32];
    char phone_number[24];
    char website[42];
    char creation_date[12];
    unsigned n_employees;
    float share_value;
};

/***************************************************************************************
* Person tuple
****************************************************************************************/
struct person {
    char type[PREF_LEN];    // "PRS"
    unsigned id;            // pk
    unsigned id_company;    // fk
    unsigned id_job;        // fk
    char title[16]; 
    char firstname[32];
    char lastname[42];
    char gender[2];
    char creation_date[12]; //struct tm creation_date; // date of creation of the record
    char phone_number[16];
    char mobile_number[16];
    char email[64];
    unsigned shares;
};
