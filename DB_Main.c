/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
*
* Programme principal : creation du fichier de donnees te remplissage des tables
*
* Programmation procedurale 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/
#include "DB_Main.h"

void test_OS(void) {
    #ifdef _WIN32
        return;
    #elif __linux__
        return;
    #else
        puts("OS not supported.");
        exit(1);
    #endif
}

/****************************************************************************************
* Main program
****************************************************************************************/
int main(void) {
    dbc db;

    test_OS();
    create_db(&db);

    import_countries(&db);
    export_countries(&db);
    load_countries(&db);
    print_countries(&db);

    import_jobs(&db);
    export_jobs(&db);
    load_jobs(&db);
    print_jobs(&db);

    import_industries(&db);
    export_industries(&db);
    load_industries(&db);
    print_industries(&db);

	return 0;
}
