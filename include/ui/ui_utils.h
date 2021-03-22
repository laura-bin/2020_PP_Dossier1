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
 * PP 2020-2021 - Laura Binacchi - Fedora 32
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
 * @param reversed: print in reversed order boolean
 */
void paginate(unsigned n, struct node* list, void (*print)(void *),
                void (*print_header)(void), int reversed);

/**
 * Prints a details list of results:
 *  - the single result found
 *  - the nearest results if no result has been found
 *
 * @param results: list size
 * @param list: linked list to print
 * @param print_detail: print function to call
 */
void print_detail_list(int results, struct node* list, void (*print_detail)(void *));

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

/**
 * Gets a yes/no answer from the user
 * (default is no)
 *
 * @return either
 *      1 if the first character entered by the user is 'Y' or 'y'
 *      0 in all other cases
 */
int get_yes_input(void);