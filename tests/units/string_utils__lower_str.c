/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Test lower string function
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/string_utils.h"

int failed = 0;

#define TEST(call, expect) do { \
        printf(#call " == " #expect ": "); \
        char *__value = call; \
        if (strcmp(__value, expect) == 0) { \
            printf("v\n"); \
        } else { \
            printf("x\n"); \
            ++failed; \
        } \
        free(__value); \
    } while (0)

int main() {
    TEST(lower_str("Some"), "some");
    TEST(lower_str("etoauAERIOer"), "etoauaerioer");
    TEST(lower_str(""), "");

    return failed;
}
