#pragma once
/** *******************************************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * User input functions:
 *  - get unsigned int
 *  - get text
 * User output functions:
 *  - pause page
 *  - pagination
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 *********************************************************************************************************************/

#include "utils/linked_list.h"

/* Number of records printed by page */
#define PAGE_SIZE   30

/**
 * Pauses the program (waits for a key to be pressed)
 */
void pause_page(void);

/**
 * Prints a linked list with pagination
 *
 * @param n: number of items to print
 * @param list: linked list to print
 * @param print: print function to call
 * @param print_header: print header function to call
 */
void paginate(unsigned n, struct node* list, void (*print)(void *),
                void (*print_header)(void));

/**
 * Gets an unsigned integer from the user
 *
 * @return a valid unsigned integer
 */
unsigned get_uns_input(void);

/**
 * Gets a string from the user
 *
 * @param out_input: user input
 * @param size: input max size
 */
void get_text_input(char *out_input, int size);
