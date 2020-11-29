/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* v 1:
*   - admin menu (by launching program with param "admin") : db file creation / deletion
*   - declarative menus
*   - database metadata display
*   - data import
*   - data export
* v1.1:
    - aligner en modulo 32
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include <string.h>

#include "menus.h"
#include "system.h"
#include "utils.h"

/***************************************************************************************
* Main program :
*   - opens the log file & the database file
*   - tests the OS
*   - launches the main menu in admin or user mode
*       (admin is launched by adding param "admin")
****************************************************************************************/
int main(int argc, char *argv[]) {
    struct db db;
    int rv;         // returned value

    // open the log file & exit the program if it fails
    make_sub_dir(DAT_DIR);
    if ((db.log_file = fopen(DAT_DIR DIR_SEP"db_clients.log", "a")) == NULL) return 1;

    // set the application mode
    if (argc == 2 && !strcmp(argv[1], "admin")) {
        db.app_mode = ADMIN;
        log_info(&db, "Main program", "Program started in admin mode");
    } else {
        db.app_mode = USER;
        log_info(&db, "Main program", "Program started in user mode");
    }

    // test the OS & exit the program if its not supported
    rv = test_OS();
    if (rv)  {
        log_info(&db, "Main program", "Program end (OS not supported)");
        return rv;
    }

    log_info(&db, "Main program", "Opening database file...");
    // complete database file path
    strcpy(db.dat_file_path, DAT_DIR DIR_SEP"db_clients.dat");

    // try to open the database file
    // in user mode, if no database is opened, the program stops
    rv = open_db(&db, READ);
    if (rv && db.app_mode == USER) {
        puts("No database file available: please contact an administrator");
        log_info(&db, "Main program", "Program stopped (no database opened in user mode)");
        fclose(db.log_file);
        return rv;
    }

    // main menu loop
    rv = main_menu(&db);

    // close file pointers
    close_db(&db);
    log_info(&db, "Main program", "Program stopped by the user");
    fclose(db.log_file);

    return rv;
}
