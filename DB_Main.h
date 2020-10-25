/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
*
* Definition des structures
*
* Programmation procedurale 2020 - Laura Binacchi
****************************************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/***************************************************************************************
* Number of reserved locations in the DB file for each type of field
****************************************************************************************/
#define N_RES_CTR 100
#define N_RES_JOB 200
#define N_RES_IND 100
#define N_RES_GRP 3000
#ifdef _WIN32
#define DIR_SEPARATOR "\\"
#else
#define DIR_SEPARATOR "/"
#endif
#define BUF_LEN 200

typedef unsigned int uint;

/***************************************************************************************
* DB header
****************************************************************************************/
typedef struct {
    uint db_size;       // DB size
    char db_name[28];   // DB name
    uint n_res_ctr;     // Number of tuples reserved in the country table
    uint n_res_job;     //      in the job table
    uint n_res_ind;     //      in the industry table
    uint n_res_grp;     //      in the group table
    uint off_ctr;       // Offset of the country table
    uint off_job;       //      of the job table
    uint off_ind;       //      of the industry table
    uint off_grp;       //      of the group table
    uint n_ctr;         // Number of tuples saved in the country table
    uint n_job;         //      in the job table
    uint n_ind;         //      in the industry table
    uint n_grp;         //      in the group table
    char filler[16];    // Filler for alignement in hex file viewer
} db_header;

/***************************************************************************************
* Country entity
****************************************************************************************/
typedef struct {
    char type[8];       // "CTR"
    uint id;            // primary key
    char name[24];      // country name
    char zone[24];      // zone
    char iso[4];        // ISO code
} country_entity;

/***************************************************************************************
* Job entity
****************************************************************************************/
typedef struct {
    char type[8];       // "JOB"
    uint id;            // primary key
    char level[30];
    char department[30];
    char name[56];
} job_entity;

/***************************************************************************************
* Industry entity
****************************************************************************************/
typedef struct {
    char type[8];       // "IND"
    uint id;            // primary key
    char sector[30];
    char name[54];
} industry_entity;

/***************************************************************************************
* Group entity
****************************************************************************************/
typedef struct {
    char type[8];       // "GRP"
    uint id;            // primary key
    char name[48];
    uint country_id;    // foreign key
} group_entity;

/***************************************************************************************
* Database
* TODO V1 delete non appropriate buffers
****************************************************************************************/
typedef struct {
    db_header header;
    country_entity countries[N_RES_CTR];   // Buffer of coutries
    job_entity jobs[N_RES_JOB];            // Buffer of jobs
    industry_entity industries[N_RES_IND]; // Buffer of industries
} dbc;

/****************************************************************************************
* Prototypes
****************************************************************************************/
void create_db(dbc *db);                // Create an empty database file

// Country table
void import_countries(dbc *db);         // imports the country csv file to dat file
void export_countries(dbc *db);         // exports the country table from dat file to csv file
void load_countries(dbc *db);           // loads the country table from the dat file to the buffer
void print_countries(dbc *db);          // prints the country table
void print_country(dbc *db, uint id);   // prints a single country from the database buffer

// Job table
void import_jobs(dbc *db);          // imports the job csv file to dat file
void export_jobs(dbc *db);          // exports the job table from dat file to csv file
void load_jobs(dbc *db);            // loads the job table from the dat file to the buffer
void print_jobs(dbc *db);           // prints the job table
void print_job(dbc *db, uint id);   // prints a single job from the database buffer

// Industry table
void import_industries(dbc *db);         // imports the industry csv file to dat file
void export_industries(dbc *db);         // exports the industry table from dat file to csv file
void load_industries(dbc *db);           // loads the industry table from the dat file to the buffer
void print_industries(dbc *db);          // prints the industry table
void print_industry(dbc *db, uint id);   // prints a single industry from the database buffer

// Group table
void import_groups(dbc *db);        // imports the group csv file to dat file
void export_groups(dbc *db);        // exports the group table from dat file to csv file
void print_groups(dbc *db);         // prints the group table from the database file