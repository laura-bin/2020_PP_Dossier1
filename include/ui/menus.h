#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Declarative menus:
 *  - admin menu: db file creation, deletion, import, etc.
 *  - user menu: db file access and operation functions
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

/* Number of menus for each application mode */
#define ADMIN_MENUS_COUNT   5
#define USER_MENUS_COUNT    14

/* Menu entry: text displayed to the user and action to call */
struct menu_entry {
    char *text;                 // text to display to the user
    int (*action)(struct db *); // action to execute when the entry is selected
};

/* Menu corresponding to an application mode (menus for the admin & menus for the user) */
struct menu {
    char *title;                        // menu title : displays the application mode
    const struct menu_entry *entries;   // list of menu entries
    unsigned entry_count;               // number of entries for the menu
};

/* Set of application menus */
extern const struct menu menus[APP_MODE_COUNT];

/**
 * Displays the main menu & call the action corresponding to the user's choice:
 *  loop until the user has chosen to quit
 *
 * @return 0 if the method has successfully been executed
 */
int main_menu(struct db *db);
