/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database creation test
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <string.h>

#include "db_file/admin.h"
#include "db_file/open_close.h"
#include "ui/menus.h"
#include "utils/logger.h"
#include "utils/system.h"

int main(void) {
    struct db db;

    // open the log file & exit the program if it fails
    make_sub_dir(DAT_DIR);
    db.log_file = fopen(DAT_DIR DIR_SEP"test_create_db.log", "a");
    
    // set the application mode
    db.app_mode = ADMIN;

    db.dat_file = NULL;
    strcpy(db.dat_file_path, DAT_DIR DIR_SEP"db_clients.dat");

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
