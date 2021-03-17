#include "utils/string_replace.h"

void string_replace(char *string, char search, char replace) {
    while (*string) {
        if (*string == search) {
            *string = replace;
        }
        ++string;
    }
}