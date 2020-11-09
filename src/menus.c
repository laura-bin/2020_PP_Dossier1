/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Menus declaratifs :
*   - definition des menus
*   - boucle d'affichage du menu / appel de la fonction correspondant au menu choisi
*
* Programmation procedurale 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include <stdarg.h>

#include "menus.h"
#include "db_file.h"
#include "system.h"
#include "utils.h"

/***************************************************************************************
* Admin mode menus
****************************************************************************************/
const struct menu_entry admin_menus[ADMIN_MENUS_COUNT] = {
    {
        .text = "Create database file",
        .action = &create_db
    },
    {
        .text = "Delete database file",
        .action = &delete_db
    }
};

/***************************************************************************************
* User mode menus
****************************************************************************************/
const struct menu_entry user_menus[USER_MENUS_COUNT] = {
    {
        .text = ".",
        .action = &dummy_fct
    },
    {
        .text = ".",
        .action = &dummy_fct
    }
};

/***************************************************************************************
* Menus for each application mode
****************************************************************************************/
const struct menu menus[APP_MODE_COUNT] = {
    {
        .title = "Admin mode",
        .entry_count = ADMIN_MENUS_COUNT,
        .entries = admin_menus
    },
    {
        .title = "User mode",
        .entry_count = USER_MENUS_COUNT,
        .entries = user_menus
    },
};

/* Clears the terminal and prints the header */
void print_header(database *db) {
    clear_terminal();
    puts("+-----------------------------------------------------------------------------------+");
    printf("| Client database: %-43s %20s |\n", 
        db->dat_file == NULL ? "no database file opened" : db->filename,
        menus[db->app_mode].title);
    puts("+-----------------------------------------------------------------------------------+");
    puts("");
}

/***************************************************************************************
* Displays the main menu & call the action corresponding to the user's choice
****************************************************************************************/
int main_menu(database *db) {
    const struct menu *menu = &menus[db->app_mode];
    unsigned i;
    unsigned choice = 1;

    while(choice) {
        print_header(db);

        for (i = 0; i < menu->entry_count; i++) {
            printf("[%d] %s.\n", i+1, menu->entries[i].text);
        }
        printf("[0] Quit.\n");
        puts("");

        choice = get_uns_input();

        // 
        if (choice == 0) {
            clear_terminal();
                puts("+-----------------------------------------------------------------------------------+");
                puts("|                                     GOODBYE !                                     |");
                puts("+-----------------------------------------------------------------------------------+");
                return 0;
        }

        // check if the menu is valid
        if (choice > menu->entry_count) {
            printf("[%d] is not a valid menu.\n", choice);
            pause_page();
            continue;
        }

        clear_terminal();
        print_header(db);
        puts(menu->entries[choice-1].text);
        puts("-------------------------------------------------------------------------------------");
        puts("");

        (*menu->entries[choice-1].action)(db);
        pause_page();
    }
    return 0;
}
