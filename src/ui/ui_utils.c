/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * User interface functions : input and output management
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "ui/ui_utils.h"
#include "utils/system.h"

/* PRIVATE FUNCTION */

/**
 * Cleans the stdin buffer
 */
void clean_stdin(void) {
    int c;
    do c = getchar();
    while (c != '\n' && c != EOF);
}

/* HEADER IMPLEMENTATION */

void pause_page(void) {
    printf("\nPress any key to continue...");
    int c = getchar();
    if (c != '\n') {
        clean_stdin();
    }
}

void paginate(unsigned n, struct node* list, void (*print)(void *),
                void (*print_header)(void), int reversed) {
    unsigned i = 0;
    unsigned page = 0;
    unsigned pages = (n+PAGE_SIZE-1) / PAGE_SIZE;

    if (!n) {
        puts("\nNo result found");
    }

    while (list != NULL) {
        if (i % PAGE_SIZE == 0) {
            clear_terminal();
            page++;
            printf("Page %u/%u\n\n", page, pages);
            printf("%9s ", "");
            (*print_header)();
            puts("");
        }

        if (reversed) {
            printf("%4u/%-4u ", n-i, n);
            (*print)(list->data);
            list = list->previous;
        } else {
            printf("%4u/%-4u ", i+1, n);
            (*print)(list->data);
            list = list->next;
        }
        i++;

        if (i % PAGE_SIZE == 0 && page != pages) pause_page();
    }
}

void print_detail_list(int results, struct node* list, void (*print_detail)(void *)) {
    clear_terminal();

    if (results == 1) {
        puts("Result found:\n");
    } else {
        puts("Nearest results:\n");
    }

    while (list != NULL) {
        (*print_detail)(list->data);
        puts("");
        list = list->next;
    }
}

unsigned get_uns_input(void) {
    int input = -1;

    while (scanf("%d", &input) != 1 || input < 0) {
        clean_stdin();
        printf("Please enter an unsigned integer: ");
    }
    clean_stdin();
    return input;
}

void get_text_input(char *out_input, int size) {
    fgets(out_input, size, stdin);

    if (out_input != NULL) {
        char *lf;
        // if there is a line feed character, delete it
        if ((lf = strchr(out_input, '\n')) != NULL) {
            *lf = '\0';
        }
        // else empty the stdin
        else clean_stdin();
    }
}

int get_yes_input(void) {
    char input;
    char yes = 0;

    scanf("%c", &input);
    if (input != '\n') {
        if (tolower(input) == 'y') {
            yes = 1;
        }
        clean_stdin();
    }

    return yes;
}
