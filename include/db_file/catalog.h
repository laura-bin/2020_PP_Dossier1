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
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stddef.h>

#include "search/search_result.h"

/* Files paths & directories */
#define DAT_DIR "data_clients"  // database file & log file directory
#define IMP_DIR "data_import"   // directory containing csv files used for import
#define EXP_DIR "data_export"   // directory containing csv files used for export
#define REP_DIR "data_report"   // directory containing data reports
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

#define ID_LEN                  10
#define MAX_LEN                 62

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

/* Numeric indexes types & count */
enum num_index {
    COMP_BY_GROUP_ID,   // company by group id
    PERS_BY_COMP_ID,    // person by company id
    NUM_INDEX_COUNT
};

enum alpha_index {
    PERS_BY_LASTNAME,   // person by lastname
    ALPHA_INDEX_COUNT
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
    int (*import)(struct db *, char *);                 // import
    int (*export)(struct db *);                         // export
    int (*load)(struct db *, int);                      // load
    void *(*compare)(struct db *, unsigned, char *);    // string comparision
    int (*compare_id)(struct db *, unsigned, unsigned); // id comparision
    void *(*read)(struct db *, unsigned);               // read a record by direct access
    void (*print)(void *);                              // print a single record
    void (*print_details)(void *);                      // print a detailed vue of a single record
    void (*print_header)(void);                         // print the table header (fields names)
};

/* Array of tables metadata */
extern const struct table_metadata tables_metadata[TAB_COUNT];

/* Numeric index metadata */
struct num_index_metadata {
    char prefix[PREFIX_LEN];                        // tuple prefix in the database
    char display_name[32];                          // name displayed to the user
    enum table table;                               // table on wich the index is based 
    unsigned (*read_value)(struct db *, unsigned);  // read the numeric indexed value
};


/* Alphanumeric index metadata */
struct alpha_index_metadata {
    char prefix[PREFIX_LEN];                            // tuple prefix in the database
    char display_name[32];                              // name displayed to the user
    enum table table;                                   // table on wich the index is based 
    void (*read_value)(struct db *, unsigned, char *);  // read the alphanumeric indexed value
};

/* Array of numeric indexes metadata */
extern const struct num_index_metadata num_indexes_metadata[NUM_INDEX_COUNT];

/* Array of alphanumeric indexes metadata */
extern const struct alpha_index_metadata alpha_indexes_metadata[ALPHA_INDEX_COUNT];

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

/* Numeric index entity */
struct num_entity {
    char type[PREFIX_LEN];
    unsigned offset;        // entity offset
    unsigned value;         // value
    char filler[16];
};

/* Alphanumeric index entity */
struct alpha_entity {
    char type[PREFIX_LEN];
    unsigned offset;        // entity offset
    unsigned left;          // left node offset
    unsigned rigth;         // right node offset
    char value[MAX_LEN];    // value
    char filler[14];
};
