#pragma once
/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* System dependent constants & functions prototypes
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

/* Directory separator */
#ifdef _WIN32
#define DIR_SEP "\\"
#else
#define DIR_SEP "/"
#endif

/**
 * Tests the operating system :
 * only Windows (32 & 64) & linux based systems are supported by the application
 * 
 * @return either:
 *          0 if the OS is supported
 *         -1 if the OS is not supported
 */
int test_OS(void);

/**
 * Clears the terminal (new page)
 * 
 * @return either
 *          0 if the command was successfully exectuted
 *         -1 if an error occured & set errno
 */
int clear_terminal(void);

/**
 * Makes a new directory in the directory from which the program is launched
 * 
 * @return mkdir or _mkdir return value:
 *          0 if the directory was successfully created
 *         -1 if an error occured & set errno
 */
int make_sub_dir(char *name);
