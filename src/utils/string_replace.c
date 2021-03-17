#include "utils/string_replace.h"

void string_replace(char *string, char search, char replace) {
    char *start = string;
    while (*string) {
        if (*string == search) {
            *string = replace;
        }
        ++string;
    }
    return start;
}