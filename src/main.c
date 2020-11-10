/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* v 1 :
*   - admin menu (by launching program with param "admin") : db file creation / deletion
*   - declarative menus
*   - database metadatas display
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
    database db;
    int rv;         // returned value

    // open the log file & exit the program if it fails
    make_sub_dir("datas");
    if ((db.log_file = fopen("datas"DIR_SEP"db_clients.log", "a")) == NULL) return 1;

    // set the application mode
    if (argc == 2 && !strcmp(argv[1], "admin")) {
        db.app_mode = ADMIN;
        log_info(&db, "Main program", "Program started by admin");
    } else {
        db.app_mode = USER;
        log_info(&db, "Main program", "Program started by user");
    }

    // test the OS & exit the program if its not supported
    rv = test_OS();
    if (rv)  {
        log_info(&db, "Main program", "Program end (OS not supported)");
        return rv;
    }

    // init database struct
    log_info(&db, "Main program", "Opening database file...");
    strcpy(db.filename, "db_clients.dat");
    strcpy(db.path, "datas"DIR_SEP"db_clients.dat");

    // try to open the database file
    open_db(&db);

    // in user mode, if no database is opened, the program stops
    if (db.dat_file == NULL && db.app_mode == USER) {
        puts("No database file available: please contact an administrator");
        log_info(&db, "Main program", "Program stopped (no database opened in user mode)");
        fclose(db.log_file);
        return 1;
    }

    // main menu loop
    rv = main_menu(&db);

    // close file pointers
    close_db(&db);
    log_info(&db, "Main program", "Program stopped by the user");
    fclose(db.log_file);

    return rv;
}
