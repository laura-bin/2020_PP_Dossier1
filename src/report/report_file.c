/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Report file creation
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <time.h>
#include <stdio.h>

#include "db_file/catalog.h"
#include "report/report_file.h"
#include "utils/system.h"

FILE *open_report_file(char *filename) {
    char file_path[255];            // report file path
    char sdt[32];                   // string formatted date time
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    // create the directory if it doesn't exist
    make_sub_dir(REP_DIR);

    // format the file path
    strftime(sdt, 32, "%F_%H-%M-%S", tm);
    sprintf(file_path, REP_DIR DIR_SEP"%s_%s_%s.txt", filename, "group_employees", sdt);

    return fopen(file_path, "w");
}