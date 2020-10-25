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
    char name[28];      // country name
    char zone[20];      // zone
    char iso[4];        // ISO code
} country_entity;

/***************************************************************************************
* Job entity
****************************************************************************************/
typedef struct {
    char type[8];       // "JOB"
    uint id;            // primary key
    char level[20];
    char department[20];
    char name[20];
} job_entity;

/***************************************************************************************
* Industry entity
****************************************************************************************/
typedef struct {
    char type[8];       // "IND"
    uint id;            // primary key
    char sector[20];
    char name[20];
} industry_entity;

/***************************************************************************************
* Group entity
****************************************************************************************/
typedef struct {
    char type[8];       // "GRP"
    uint id;            // primary key
    char name[20];
    char country_iso[4];
    uint country_id;    // foreign key
} group_entity;

/***************************************************************************************
* Database
****************************************************************************************/
typedef struct {
    db_header header;
    country_entity countries[N_RES_CTR];   // Buffer of coutries
} dbc;

/****************************************************************************************
* Prototypes
****************************************************************************************/
void create_db(dbc *db);                // Create an empty database file

void import_countries(dbc *db);         // imports country csv file to dat file
void export_countries(dbc *db);         // exports country table from dat file to csv file
void load_countries(dbc *db);           // loads the country table from the dat file to the buffer
void print_countries(dbc *db);          // prints the country table
void print_country(dbc *db, int id);    // prints a single country from thedatabase buffer
