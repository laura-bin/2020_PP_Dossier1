#pragma once
/** *******************************************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 * 
 * Logger functions prototypes
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 *********************************************************************************************************************/

#include "db_file/database.h"

/**
 * Logs a message into the log file
 * 
 * @param db: database information stored in RAM
 * @param from: string containig from where comes the log message
 * @param msg: string containig the log message
 */
void log_info(struct db *db, char *from, char *msg);

/**
 * Logs an error message into the log file using errno as log message
 * 
 * @param db: database information stored in RAM
 * @param from: string containig from where comes the log message
 */
void log_error(struct db *db, char *from);
