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
 * Opens a report file with a formatted name
 * creates the directory if it doesn't exist
 * 
 * @param filename: filename
 * 
 * @return either
 *      the file pointer
 *      NULL if an error occured
 */
FILE *open_report_file(char *filename);