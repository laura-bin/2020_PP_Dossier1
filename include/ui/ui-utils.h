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
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 *********************************************************************************************************************/

/**
 * Pauses the program (waits for a key to be pressed)
 */
void pause_page(void);

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
