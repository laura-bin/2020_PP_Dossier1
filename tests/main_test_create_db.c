/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database creation test:
 *  - import and export data
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <string.h>

#include "db_file/admin.h"
#include "db_file/open_close.h"
#include "ui/menus.h"
#include "utils/logger.h"
#include "utils/system.h"

int main(int argc, char *argv[]) {
    struct db db;

    // open the log file & exit the program if it fails
    make_sub_dir(DAT_DIR);
    if ((db.log_file = fopen(DAT_DIR DIR_SEP"db_clients.log", "a")) == NULL) {
        perror("Opening log file");
        return 1;
    }

    log_info(&db, "Test db creation", "Start");
    
    // set the application mode
    db.app_mode = ADMIN;

    strcpy(db.dat_file_path, DAT_DIR DIR_SEP"db_clients.dat");
    open_db(&db, READ);

    // create the empty database file
    create_db(&db);

    // import data from csv files
    import(&db);

    // export data from csv files
    export(&db);

    //display metadata
    display_metadata(&db);

    // close file pointers
    close_db(&db);
    log_info(&db, "Test db creation", "End");
    fclose(db.log_file);

    return 0;
}
