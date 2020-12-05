/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Menus :
 *  - assignation of the text and the action to each menu
 *  - menu loop: diplays text and calls the action chosen by the user
 * 
 * Private functions
 *  - UI management (print & get user's inputs)
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/db_file.h"
#include "menus.h"
#include "utils/system.h"
#include "utils/logger.h"

/* Admin mode menus assignation */
const struct menu_entry admin_menus[ADMIN_MENUS_COUNT] = {
    {
        .text = "Create database file",
        .action = &create_db
    },
    {
        .text = "Import data (from csv files to dat file)",
        .action = &import
    },
    {
        .text = "Export data (from dat file to csv files)",
        .action = &export
    },
    {
        .text = "Delete database file",
        .action = &delete_db
    },
    {
        .text = "Display database file metadata",
        .action = &display_metadata
    }
};

/* User mode menus assignation */
const struct menu_entry user_menus[USER_MENUS_COUNT] = {
    {
        .text = ".",
        .action = NULL
    }
};

/* Menus for each application mode assignation */
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

/* PRIVATE FUNCTIONS */

/**
 * Cleans the stdin buffer
 */
void clean_stdin(void) {
    int c;
    do c = getchar();
    while (c != '\n' && c != EOF);
}

/**
 * Pauses the program (waits for a key to be pressed)
 */
void pause_page(void) {
    printf("\nPress any key to continue...");
    int c = getchar();
    if (c != '\n') clean_stdin();
}

/**
 * Gets an unsigned integer from the user
 * 
 * @return a valid unsigned integer
 */
unsigned get_uns_input(void) {
    int input = -1;

    while (scanf("%d", &input) != 1 || input < 0) {
        clean_stdin();
        printf("Please enter an unsigned integer: ");
    }
    clean_stdin();
    return input;
}

/**
 * Clears the terminal and prints the header
 * 
 * @param db: database information stored in RAM
 */
void print_header(struct db *db) {
    clear_terminal();
    puts("+-----------------------------------------------------------------------------------+");
    printf("| Client database: %-43s %20s |\n", 
        db->dat_file == NULL ? "no database file opened" : db->header.db_name,
        menus[db->app_mode].title);
    puts("+-----------------------------------------------------------------------------------+");
    puts("");
}

/* HEADER IMPLEMENTATION */

int main_menu(struct db *db) {
    const struct menu *menu = &menus[db->app_mode]; // menus (display name + action)
    unsigned choice = 1;                            // user menu choice
    unsigned i;
    
    while(1) {
        // print the menu
        print_header(db);
        for (i = 0; i < menu->entry_count; i++) {
            printf("[%d] %s\n", i+1, menu->entries[i].text);
        }
        printf("[0] Quit\n");
        puts("");

        // get the user choice
        choice = get_uns_input();

        // check if this choice is valid
        if (choice > menu->entry_count) {
            printf("[%d] is not a valid menu\n", choice);
            pause_page();
            continue;
        }

        // call the  corresponding action
        clear_terminal();
        if (choice == 0) {
                puts("+-----------------------------------------------------------------------------------+");
                puts("|                                     GOODBYE !                                     |");
                puts("+-----------------------------------------------------------------------------------+");
                return 0;
        }
        print_header(db);
        puts(menu->entries[choice-1].text);
        puts("-------------------------------------------------------------------------------------");
        puts("");
        (*menu->entries[choice-1].action)(db);
        pause_page();
    }
}
