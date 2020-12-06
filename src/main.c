/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * v1:
 *  - admin menu (by launching program with param "admin") : db file creation / deletion
 *  - declarative menus
 *  - database metadata display
 *  - data import
 *  - data export
 * v1.1:
 *  - adapt field size to view in 32 bytes line hex editor
 *  - use standard comments https://www.doxygen.nl/manual/docblocks.html
 *  - improve values returned (use more the values returned by the method called
 *      and document when errno is set)
 *  - improve log messages
 * v2:
 *  - load code tables into buffers
 *  - print code tables
 *  - files reorganizations: splitting db_file methods into distinct files, etc.
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <string.h>

#include "db_file/db_file_utils.h"
#include "ui/menus.h"
#include "utils/logger.h"
#include "utils/system.h"

/**
 * Main program :
 *  - opens the log file & the database file
 *  - tests the OS
 *  - launches the main menu in admin or user mode
 *      (admin is launched by adding arg "admin")
 *  - all other arg is ignored
 */
int main(int argc, char *argv[]) {
    struct db db;   // RAM stored database information
    int rv;         // value returned by the main menu loop

    // open the log file & exit the program if it fails
    make_sub_dir(DAT_DIR);
    if ((db.log_file = fopen(DAT_DIR DIR_SEP"db_clients.log", "a")) == NULL) {
        perror("Opening log file");
        return 1;
    }

    // set the application mode
    if (argc > 1 && !strcmp(argv[1], "admin")) {
        db.app_mode = ADMIN;
        log_info(&db, "Main program", "Program started in admin mode");
    } else {
        db.app_mode = USER;
        log_info(&db, "Main program", "Program started in user mode");
    }

    // test the OS & exit the program if it is not supported
    if (test_OS())  {
        log_info(&db, "Main program", "Program stopped (OS not supported)");
        fprintf(stderr, "Impossible to launch the program: OS is not supported\n");
        return 1;
    }

    // try to open the database file:
    // - in user mode, if no database is opened, the program stops
    // - in admin mode, the program continues
    //      and the terminal header shows that no database is opened
    strcpy(db.dat_file_path, DAT_DIR DIR_SEP"db_clients.dat");
    if (open_db(&db, READ) && db.app_mode == USER) {
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
