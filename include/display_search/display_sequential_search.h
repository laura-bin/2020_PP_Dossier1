#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database file sequential searches in code tables (country, job, industry, group)
 * displayed on the standard output
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

/**
 * Displays countries containing a substring entered by the user
 *
 * @param db: database information stored in RAM
 */
int search_countries(struct db *db);

/**
 * Displays jobs containing a substring entered by the user
 *
 * @param db: database information stored in RAM
 */
int search_jobs(struct db *db);

/**
 * Displays industries containing a substring entered by the user
 *
 * @param db: database information stored in RAM
 */
int search_industries(struct db *db);

/**
 * Displays groups containing a substring entered by the user
 *
 * @param db: database information stored in RAM
 */
int search_groups(struct db *db);
