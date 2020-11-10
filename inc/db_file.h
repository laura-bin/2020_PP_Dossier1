#pragma once
/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Database file :
*   - header (database file metadatas)
*   - struct database used to pass database informations throw the program functions
*   - database access functions : create, delete, read, etc.
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include <stdio.h>

#include "catalog.h"

/***************************************************************************************
* Database file header
****************************************************************************************/
struct header {
    unsigned size;                  // db file size
    char db_name[36];               // db name
    unsigned offset[TAB_COUNT];     // offset of each table
    unsigned n_reserved[TAB_COUNT]; // number of tuples reserved in each table
    unsigned n_recorded[TAB_COUNT]; // number of tuples saved in each table
};

/***************************************************************************************
* Informations about the database used by the main program
****************************************************************************************/
typedef struct {
    int app_mode;                           // application mode : admin or user
    char filename[32];                      // database filename
    char path[255];                         // database file relative path
    FILE *dat_file;                         // database file pointer
    FILE *log_file;                         // log file pointer
    struct header header;                   // database header
    struct country countries[N_RES_CTR];    // buffer of coutries (sorted)
    struct job jobs[N_RES_JOB];             // buffer of jobs (sorted)
    struct industry industries[N_RES_IND];  // buffer of industries (sorted)
    struct group groups[N_RES_IND];         // buffer of groups (sorted)
} database;

/***************************************************************************************
* Database file creation
****************************************************************************************/
int create_db(database *db);            // creates an empty database file
int delete_db(database *db);            // deletes the database file
int open_db(database *db);              // opens the database file in read mode
int close_db(database *db);             // closes the database file
int display_metadatas(database *db);    // displays the database metadatas
int dummy_fct(database *db);