/** *******************************************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 * 
 * Logger functions implementation
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 *********************************************************************************************************************/

#include <errno.h>
#include <string.h>
#include <time.h>

#include "utils/logger.h"

void log_info(struct db *db, char *from, char *msg) {
    char sdt[64]; // string containing the datetime
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    // format the date time string
    strftime(sdt, sizeof(sdt), "%F %T", tm);

    // log info into the log file
    fprintf(db->log_file, "%s %s: %s\n", sdt, from, msg);
    fflush(db->log_file);
}

void log_error(struct db *db, char *from) {
    log_info(db, from, strerror(errno));
}
