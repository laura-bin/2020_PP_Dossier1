#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database file views:
 *  - print code tables from their buffers (county, job, industry, group)
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "database.h"

/**
 * Prints the country table from the buffer
 *
 * @param db: database information stored in RAM
 */
int print_countries(struct db *db);

/**
 * Prints the job table from the buffer
 *
 * @param db: database information stored in RAM
 */
int print_jobs(struct db *db);

/**
 * Prints the industry table from the buffer
 *
 * @param db: database information stored in RAM
 */
int print_industries(struct db *db);

/**
 * Prints the group table from the buffer
 *
 * @param db: database information stored in RAM
 */
int print_groups(struct db *db);
