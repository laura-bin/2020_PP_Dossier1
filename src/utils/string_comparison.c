/** *******************************************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * String comparison function
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 *********************************************************************************************************************/

#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "utils/string_comparison.h"

char* lower_str(char *str) {
    size_t i;
    char *new_str = malloc(strlen(str)+1);

    for (i = 0; i < strlen(str); i++) new_str[i] = tolower(str[i]);
    new_str[i] = '\0';

    return new_str;
}

int contain_icase(int n_str, char *substr, ...) {
    va_list args;
    int found = 0;
    char *searched = lower_str(substr);

    va_start(args, substr);
    while (n_str > 0 && !found) {
        char *str = lower_str(va_arg(args, char*));
        if (strstr(str, searched)) found = 1;
        free(str);
        n_str--;
    }

    va_end(args);
    free(searched);

    return found;
}

int start_with_icase(char *string, char *searched) {
    int found = 0;
    char *lower_string;
    char *lower_searched;
    size_t searched_len = strlen(searched);

    if (searched_len > strlen(string)) {
        return -1;
    }

    lower_string = lower_str(string);
    lower_searched = lower_str(searched);

    found = strncmp(lower_searched, lower_string, searched_len);

    free(lower_string);
    free(lower_searched);

    return found;
}
