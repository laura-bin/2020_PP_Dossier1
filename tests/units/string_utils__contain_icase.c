/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Test string contains (case insensitive) function
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdio.h>

#include "utils/string_utils.h"

int failed = 0;

#define TEST(expect, call) do { \
        printf("%d == " #call ": ", expect); \
        if (expect == call) { \
            printf("v\n"); \
        } else { \
            printf("x\n"); \
            ++failed; \
        } \
    } while (0)

int main() {
    TEST(1, contain_icase(2, "some", "Some string", "other string"));
    TEST(0, contain_icase(2, "some string", "bloup", "stuff"));
    TEST(1, contain_icase(2, "StR", "bloup", "some sTring"));
    TEST(1, contain_icase(3, "ou", "bloup", "wouplidou", "azerhouehr"));
    TEST(0, contain_icase(0, "wouplidou"));
    TEST(1, contain_icase(1, "", "wouplidou"));

    return failed;
}