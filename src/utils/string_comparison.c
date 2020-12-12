/** *******************************************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * String comparison function
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 *********************************************************************************************************************/

#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "utils/string_comparison.h"

/* PRIVATE METHOD */

/**
 * Creates a new lowercase string from a given string
 * /!\ free after use
 *
 * @param str: string to lower
 *
 * @return the lowercase string
 */
char* lower_str(char *str) {
    size_t i;
    char *new_str = malloc(strlen(str)+1);

    for (i = 0; i < strlen(str); i++) new_str[i] = tolower(str[i]);
    new_str[i] = '\0';

    return new_str;
}

/* HEADER IMPLEMENTATION */

int contains_icase(int n_str, ...) {
    va_list args;
    va_start(args, n_str);
    int found = 0;

    char *substr = lower_str(va_arg(args, char*));

    while (n_str > 0 && !found) {
        char *str = lower_str(va_arg(args, char*));
        if (strstr(str, substr)) found = 1;
        free(str);
        n_str--;
    }

    free(substr);
    va_end(args);
    return found;
}
