#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Report file creation
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

/**
 * Creates a new report file with a formatted name
 * creates the directory if it doesn't exist
 * 
 * @param filename: filename
 * 
 * @return either
 *      the file pointer opened in write mode
 *      NULL if an error occured
 */
FILE *create_report_file(char *filename);
