#pragma once
/**********************************************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
 * 
 * Utils functions prototypes
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 *********************************************************************************************************************/

#include "db_file.h"

void clean_stdin(void);                                 // cleans the stdin buffer
void pause_page(void);                                  // pauses the program (waits for a key to be pressed)
unsigned get_uns_input(void);                           // gets a valid unsigned integer from the user
void log_info(struct db *db, char *from, char *msg);    // logs a message into the log file
void log_error(struct db *db, char *from);              // logs an error message into the log file using errno
