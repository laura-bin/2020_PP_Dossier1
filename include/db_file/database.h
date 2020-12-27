#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database structure used to store database information in RAM
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdio.h>

#include "catalog.h"

/* Application modes & count */
enum app_mode {
    ADMIN,
    USER,
    APP_MODE_COUNT
};

/* Database file header */
struct header {
    unsigned size;                      // db file size
    char db_name[28];                   // db name
    unsigned table_off[TAB_COUNT];      // tables offsets
    unsigned index_off[INDEX_COUNT];    // indexes offsets
    unsigned n_table_res[TAB_COUNT];    // number of tuples reserved in each table
    unsigned n_index_res[INDEX_COUNT];  // number of tuples reserved in each index
    unsigned n_table_rec[TAB_COUNT];    // number of tuples saved in each table
    unsigned n_index_rec[INDEX_COUNT];  // number of tuples saved in each index
};

/* Informations about the database used by the main program */
struct db {
    enum app_mode app_mode;                 // application mode : admin or user
    char dat_file_path[255];                // database file relative path
    FILE *dat_file;                         // database file pointer
    FILE *log_file;                         // log file pointer
    FILE *csv_file;                         // csv file pointer
    struct header header;                   // database header
    struct country countries[N_RES_CTR];    // buffer of coutries (sorted)
    struct job jobs[N_RES_JOB];             // buffer of jobs (sorted)
    struct industry industries[N_RES_IND];  // buffer of industries (sorted)
    struct group groups[N_RES_GRP];         // buffer of groups (sorted)
};