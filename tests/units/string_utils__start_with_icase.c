/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Test string start with (case insesitive) function
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdio.h>

#include "utils/string_utils.h"

int failed = 0;

#define TEST(call, expect) do { \
        printf(#call " " #expect ": "); \
        if (call expect) { \
            printf("v\n"); \
        } else { \
            printf("x\n"); \
            ++failed; \
        } \
    } while (0)

int main() {
    TEST(start_with_icase("some", "Some string"), > 0);
    TEST(start_with_icase("some", "some string"), > 0);
    TEST(start_with_icase("some string", "some"), == 0);
    TEST(start_with_icase("soMe string", "sOme"), == 0);
    TEST(start_with_icase("some string", "bloup"), < 0);
    TEST(start_with_icase("StR", "bloup"), < 0);
    TEST(start_with_icase("oups", "ou"), == 0);
    TEST(start_with_icase("", "wouplidou"), > 0);
    TEST(start_with_icase("wouplidou", ""), == 0);

    return failed;
}