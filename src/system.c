/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* System dependent functions
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include <stdio.h>

#include "utils.h"

#ifdef _WIN32 // win 32 or win64
#include <windows.h>
#include <conio.h>
#include <direct.h>
#endif

#ifdef __linux__
#include <stdlib.h>
#include <sys/stat.h>
#endif

/***************************************************************************************
* Tests the operating system :
* only Windows (32 & 64) & linux based systems are supported by the application
****************************************************************************************/
int test_OS(void) {
    #ifdef _WIN32
        return 0;
    #elif __linux__
        return 0;
    #else
        return 1;
    #endif
}

/***************************************************************************************
* Clears the terminal (new page)
****************************************************************************************/
void clear_terminal(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/***************************************************************************************
* Makes a new directory in the directory from which the program is launched
****************************************************************************************/
void make_sub_dir(char *new_dir) {
#ifdef _WIN32
    _mkdir(new_dir);
#else
    mkdir(new_dir, 0700);
#endif
}
