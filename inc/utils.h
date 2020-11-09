#pragma once
/**********************************************************************************************************************
 * Programmation procédurale - AGENDA V1
 * =====================================
 * 
 * Utils functons :
 *
 * Laura Binacchi - 2020 - Fedora 32
 *********************************************************************************************************************/

#include "db_file.h"

// enum error_type {
//     OPEN_FILE,
// };

// void print_error(int err);
void clean_stdin(void);                                 // cleans the stdin buffer
unsigned get_uns_input(void);                           // gets a valid unsigned integer from the user
void log_info(database *db, char *from, char *msg);     // logs a message into the log file
void log_error(database *db, char *from);               // logs an error message into the log file using errno

// void get_text_input(char *input, int buf_size);