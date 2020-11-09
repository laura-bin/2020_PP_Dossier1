#pragma once
/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* System dependent constants & functions prototypes
*
* Programmation procedurale 2020 - Laura Binacchi - Fedora 32
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
void pause_page(void);              // pauses the programs (waits for a key to be pressed)
void make_sub_dir(char name[255]);  // makes a new directory in the directory from which the program is launched
