#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database file sequential searches in code tables (county, job, industry, group)
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "database.h"

/**
 * Prints the country table from the buffer
 *
 * @param db: database information stored in RAM
 */
int search_countries(struct db *db);

/**
 * Prints the job table from the buffer
 *
 * @param db: database information stored in RAM
 */
int search_jobs(struct db *db);

/**
 * Prints the industry table from the buffer
 *
 * @param db: database information stored in RAM
 */
int search_industries(struct db *db);

/**
 * Prints the group table from the buffer
 *
 * @param db: database information stored in RAM
 */
int search_groups(struct db *db);
