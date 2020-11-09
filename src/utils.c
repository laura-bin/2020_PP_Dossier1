#include <errno.h>
#include <stdio.h>
#include <time.h>

// #include <stdlib.h>
#include <string.h>

#include "db_file.h"


// /* Catches an error */
// void print_error(int err) {
//     switch (err) {
//         case OPEN_FILE:
//             perror("Opening file");
//         break;
//     default:
//         break;
//     }
//     return;
// }

// /* Cleans the stdin buffer */
void clean_stdin(void) {
    int c;
    do c = getchar();
    while (c != '\n' && c != EOF);
}

/* Returns an integer input */
unsigned get_uns_input(void) {
    int input = -1;

    while (scanf("%d", &input) != 1 || input < 0) {
        clean_stdin();
        printf("Please enter an unsigned integer: ");
    }
    clean_stdin();
    return input;
}

// /* Returns a string input */
// void get_text_input(char *input, int buf_size) {
//     fgets(input, buf_size, stdin);

//     if (input != NULL) {
//         char *lf;
//         // if there is a line feed character, delete it
//         if ((lf = strchr(input, '\n')) != NULL) *lf = '\0';
//         // else empty the stdin
//         else clean_stdin();
//     }
//     return;
// }

/* Logs a message into the log file */
void log_info(database *db, char *from, char *msg) {
    char sdt[64];                   // string containing the datetime
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // format the date time string
	sprintf(sdt, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900,
                tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    
    // log info to the log file
    fprintf(db->log_file, "%s %s: %s\n", sdt, from, msg);
}

/* Logs an error message into the log file using errno 
 * & displays the same message to the user */
void log_error(database *db, char *from) {
    char sdt[64];                   // string containing the datetime
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // format the date time string
	sprintf(sdt, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900,
                tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    
    // log errno error message in the log file
    fprintf(db->log_file, "%s %s: %s\n", sdt, from, strerror(errno));
}

