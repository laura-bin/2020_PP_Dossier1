#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Catalog:
 *  - fields length constants
 *  - tables & indexes metadata
 *  - tables & indexes structures
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stddef.h>

/* Files paths & directories */
#define DAT_DIR "data_clients"  // database file & log file directory
#define IMP_DIR "data_import"   // directory containing csv files used for import
#define EXP_DIR "data_export"   // directory containing csv files used for export
#define CSV_BUF_LEN 1024        // buffer length used on read/write csv files

/* Number of reserved locations in the DB file for each type of tuple */
#define N_RES_CTR 100
#define N_RES_JOB 200
#define N_RES_IND 100
#define N_RES_GRP 3000
#define N_RES_CMP 100000
#define N_RES_PRS 500000

/* Fields length */
#define PREFIX_LEN              8
#define COUNTRY_NAME_LEN        16
#define COUNTRY_ZONE_LEN        16
#define COUNTRY_ISO_LEN         4

#define JOB_LEVEL_LEN           22
#define JOB_DEPARTMENT_LEN      24
#define JOB_NAME_LEN            38

#define INDUSTRY_SECTOR_LEN     20
#define INDUSTRY_NAME_LEN       32

#define GROUP_NAME_LEN          32

#define COMPANY_NAME_LEN        62
#define COMPANY_ADDRESS_LEN     60
#define COMPANY_ZIP_CODE_LEN    12
#define COMPANY_CITY_LEN        32
#define COMPANY_PHONE_LEN       20
#define COMPANY_WEBSITE_LEN     38
#define COMPANY_CREATION_LEN    12

#define PERSON_TITLE_LEN        12
#define PERSON_FIRSTNAME_LEN    30
#define PERSON_LASTNAME_LEN     38
#define PERSON_GENDER_LEN       2
#define PERSON_CREATION_LEN     12
#define PERSON_PHONE_LEN        14
#define PERSON_MOBILE_LEN       14
#define PERSON_EMAIL_LEN        58

#define ID_LEN                  12

/* Types of tables & table count */
enum table {
    COUNTRY,
    JOB,
    INDUSTRY,
    GROUP,
    COMPANY,
    PERSON,
    TAB_COUNT
};

/* Indexes & count */
enum index {
    PERS_BY_COMP_ID,    // person by company id
    PERS_BY_LASTNAME,   // person by lastname
    INDEX_COUNT
};

/* Table metadata */
struct db;
struct table_metadata {
    char prefix[PREFIX_LEN];    // tuple prefix in the database
    char display_name[32];      // name displayed to the user
    unsigned n_reserved;        // number of tuples reserved in the table
    size_t size;                // tuple size
    char csv_path[255];         // csv file path used to import data
    char csv_header[255];       // csv file header
    int (*import)(struct db *, char *);         // import function pointer
    int (*export)(struct db *);                 // export function pointer
    int (*load)(struct db *, int);              // load function pointer
    void *(*compare)(struct db *, unsigned, char *);    // string comparision function
    void (*print)(void *);                              // print a single record function
    void (*print_header)(void);                 // print the table header (fields names)
};

/* Array of tables metadata */
extern const struct table_metadata tables_metadata[TAB_COUNT];

/* Index metadata */
struct index_metadata {
    char prefix[PREFIX_LEN];    // tuple prefix in the database
    unsigned n_reserved;        // number of tuples reserved in the table
    size_t size;                // tuple size
};

/* Array of indexes metadata */
extern const struct index_metadata indexes_metadata[INDEX_COUNT];

/* Country tuple */
struct country {
    char type[PREFIX_LEN];  // "CTR"
    unsigned id;            // pk
    char name[COUNTRY_NAME_LEN];
    char zone[COUNTRY_ZONE_LEN];
    char iso[COUNTRY_ISO_LEN];
    char filler[16];
};

/* Job tuple */
struct job {
    char type[PREFIX_LEN];  // "JOB"
    unsigned id;            // pk
    char level[JOB_LEVEL_LEN];
    char department[JOB_DEPARTMENT_LEN];
    char name[JOB_NAME_LEN];
};

/* Industry tuple */
struct industry {
    char type[PREFIX_LEN];  // "IND"
    unsigned id;            // pk
    char sector[INDUSTRY_SECTOR_LEN];
    char name[INDUSTRY_NAME_LEN];
};

/* Group tuple */
struct group {
    char type[PREFIX_LEN];  // "GRP"
    unsigned id;            // pk
    char name[GROUP_NAME_LEN];
    unsigned country_id;    // fk
    char filler[16];
};

/* Company tuple */
struct company {
    char type[PREFIX_LEN];  // "CMP"
    unsigned id;            // pk
    unsigned id_group;      // fk
    unsigned id_country;    // fk
    unsigned id_industry;   // fk
    char name[COMPANY_NAME_LEN];
    char address[COMPANY_ADDRESS_LEN];
    char zip_code[COMPANY_ZIP_CODE_LEN];
    char city[COMPANY_CITY_LEN];
    char phone_number[COMPANY_PHONE_LEN];
    char website[COMPANY_WEBSITE_LEN];
    char creation_date[COMPANY_CREATION_LEN];
    unsigned n_employees;
    float share_value;
    char filler[20];
};

/* Person tuple */
struct person {
    char type[PREFIX_LEN];  // "PRS"
    unsigned id;            // pk
    unsigned id_company;    // fk
    unsigned id_job;        // fk
    char title[PERSON_TITLE_LEN];
    char firstname[PERSON_FIRSTNAME_LEN];
    char lastname[PERSON_LASTNAME_LEN];
    char gender[PERSON_GENDER_LEN];
    char creation_date[PERSON_CREATION_LEN];
    char phone_number[PERSON_PHONE_LEN];
    char mobile_number[PERSON_MOBILE_LEN];
    char email[PERSON_EMAIL_LEN];
    unsigned shares;
    char filler[20];
};

/* Person by company id index */
struct person_by_company {
    char type[PREFIX_LEN];  // "PRS_CMP"
    unsigned company_id;
    unsigned offset;
    char filler[16];
};

/* Person by lastname index */
struct person_by_lastname {
    char type[PREFIX_LEN];  // "PRS_LN"
    char lastname[PERSON_LASTNAME_LEN];
    unsigned offset;
    char filler[10];
};
