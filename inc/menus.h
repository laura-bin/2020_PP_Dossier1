#pragma once
/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Menus declaratifs :
*   - menu admin : creation / suppression du fichier de base de donnees
*   - menu utilisateur : consultation du fichier de base de donnees
*
* Programmation procedurale 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include "db_file.h"

/***************************************************************************************
* Number of menus for each application mode
****************************************************************************************/
#define ADMIN_MENUS_COUNT   2
#define USER_MENUS_COUNT    2

/***************************************************************************************
* Application modes & count
****************************************************************************************/
enum app_mode {
    ADMIN,
    USER,
    APP_MODE_COUNT
};

/***************************************************************************************
* Menu entry : text displayed to the user and action to call
****************************************************************************************/
struct menu_entry {
    char text[255];                     // text to display to the user
    int (*action)(database *db);        // action to execute when the entry is selected
};

/***************************************************************************************
* Menu corresponding to an application mode (menus for the admin & menus for the user)
****************************************************************************************/
struct menu {
    char *title;                        // menu title : displays the application mode
    const struct menu_entry *entries;   // list of menu entries
    unsigned entry_count;               // number of entries for the menu
};

/***************************************************************************************
* Set of application menus
****************************************************************************************/
extern const struct menu menus[APP_MODE_COUNT];

/***************************************************************************************
* Displays the menu corresponding to the mode and calls the actions called by the user
****************************************************************************************/
int main_menu(database* db);
