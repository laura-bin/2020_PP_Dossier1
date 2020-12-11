/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * User interface function:
 *  -
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdio.h>
#include <string.h>

#include "ui/ui-utils.h"

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
    if (c != '\n') clean_stdin();
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
        if ((lf = strchr(out_input, '\n')) != NULL) *lf = '\0';
        // else empty the stdin
        else clean_stdin();
    }
    return;
}
