#pragma once
/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Country table functions prototypes:
*   - import
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include "database.h"

/***************************************************************************************
* Import a country from the csv file to the dat file
****************************************************************************************/
int import_country(struct db *db, char *csv_line, unsigned line_len);
