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
 * v2.1:
 *  - fix window / linux compatibility issues for csv files (carriage return)
 * v3:
 *  - pagination
 *  - generic linked lists
 *  - sequential searches in code tables
 * v3.1:
 *  - use constants to define fields length
 * v4:
 *  - quick sort algorithm (using stdlib qsort prototype)
 *  - numeric indexes creation: company by group id & person by company id
 *  - alphanumeric index creation: person by lastname
 *  - search group by id (binary search)
 *  - search company by id (binary search)
 *  - search person by id (binary search)
 *  - search company by group id (numeric index + binary search adaptation)
 *  - search person by company id (numeric index + binary search adaptation)
 *  - search person by lastname (alphanumeric index + binary tree)
 * v4.1:
 *  - print the linked lists in reversed order
 * v5:
 *  - split search functions
 *  - report group employees grouped by company (detail report)
 *  - report group companies grouped by country (detail report)
 * 
 * TODO :
 *  - reports
 *  - rapports (txt ou rtf) + date dans le nom du fichier de sortie
 *  - rapport de détail : liste des personnes travaillant pour chaque compagnie d'un groupe
 *  - rapport de détail : liste de toutes les compagnies appartenant à un groupe par pays
 *  - rapport aggrégé (group by) : nombre de personnes par groupe (somme des n_emp) et nombre de personnes connues dans la db (count) -> pourcentage de personnes connues dans la db
 *  - rapport aggrégé : valeur totale des actions détenues par les employés pour un groupe donné, éclaté par genre et niveau de fonction
 *  - rapports aggrégés : garder les données dans des listes chaînées
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <string.h>

#include "db_file/open_close.h"
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
