#pragma once
/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Database file :
*   - header (database file metadatas)
*   - database access functions : create, delete, read, etc.
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include <stdio.h>

#include "catalog.h"
#include "database.h"

/***************************************************************************************
* Opening mode for the database file
****************************************************************************************/
enum opening_mode {
    READ,
    WRITE,
    APPEND
};


/***************************************************************************************
* Database file creation
****************************************************************************************/
int create_db(struct db *db);                       // creates an empty database file
int delete_db(struct db *db);                       // deletes the database file
int import(struct db *db);                          // imports dats from csv files to dat file
int open_db(struct db *db, enum opening_mode mode); // opens the database file in read mode
int close_db(struct db *db);                        // closes the database file
int display_metadatas(struct db *db);               // displays the database metadatas
int dummy_fct(struct db *db);