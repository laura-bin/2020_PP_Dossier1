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

int test_OS(void) {
    #ifdef _WIN32
        return 0;
    #elif __linux__
        return 0;
    #else
        return -1;
    #endif
}

int clear_terminal(void) {
// system (linux & win) return the value that is returned by the command interpreter
#ifdef _WIN32
    if (system("cls") == -1) return -1;
    return 0;
#else
    if (system("clear") == -1) return -1;
    return 0;
#endif
}

int make_sub_dir(char *new_dir) {
#ifdef _WIN32
    return _mkdir(new_dir);
#else
    return mkdir(new_dir, 0700);
#endif
}
