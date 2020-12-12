#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database file sequential searches in code tables (country, job, industry, group)
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "database.h"

/**
 * Searches if a country contains a substring entered by the user
 *
 * @param db: database information stored in RAM
 */
int search_countries(struct db *db);

/**
 * Searches if a job contains a substring entered by the user
 *
 * @param db: database information stored in RAM
 */
int search_jobs(struct db *db);

/**
 * Searches if an industry contains a substring entered by the user
 *
 * @param db: database information stored in RAM
 */
int search_industries(struct db *db);

/**
 * Searches if a group contains a substring entered by the user
 *
 * @param db: database information stored in RAM
 */
int search_groups(struct db *db);
