#pragma once
/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* System dependent constants & functions prototypes
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

/***************************************************************************************
* Directory separator
****************************************************************************************/
#ifdef _WIN32
#define DIR_SEP "\\"
#else
#define DIR_SEP "/"
#endif

int test_OS(void);                  // tests OS : return 0 for linux & Windows, else returns 1
void clear_terminal(void);          // clears the terminal (new page)
void make_sub_dir(char *name);      // makes a new directory in the directory from which the program is launched
