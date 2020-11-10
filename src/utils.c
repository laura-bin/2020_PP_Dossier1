/**********************************************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
 * 
 * Utils functions
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 *********************************************************************************************************************/

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "db_file.h"


/***************************************************************************************
* Cleans the stdin buffer
****************************************************************************************/
void clean_stdin(void) {
    int c;
    do c = getchar();
    while (c != '\n' && c != EOF);
}

/***************************************************************************************
* Pauses the program (waits for a key to be pressed)
****************************************************************************************/
void pause_page(void) {
    printf("\nPress any key to continue...");
    int c = getchar();
    if (c != '\n') clean_stdin();
}

/***************************************************************************************
* Returns an unsigned integer from the user
****************************************************************************************/
unsigned get_uns_input(void) {
    int input = -1;

    while (scanf("%d", &input) != 1 || input < 0) {
        clean_stdin();
        printf("Please enter an unsigned integer: ");
    }
    clean_stdin();
    return input;
}

/***************************************************************************************
* Logs a message into the log file
****************************************************************************************/
void log_info(database *db, char *from, char *msg) {
    char sdt[64]; // string containing the datetime
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // format the date time string
	sprintf(sdt, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900,
                tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    
    // log info to the log file
    fprintf(db->log_file, "%s %s: %s\n", sdt, from, msg);
}

/***************************************************************************************
* Logs an error message into the log file using errno
****************************************************************************************/
void log_error(database *db, char *from) {
    log_info(db, from, strerror(errno));
}
