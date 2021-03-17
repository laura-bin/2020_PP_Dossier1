#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/string_replace.h"

int failed = 0;

#define TEST(orig, from, to, expect) do { \
        char _str[] = orig; \
        string_replace(_str, from, to); \
        char _r = strcmp(_str, expect) == 0 ? 'v' : 'x'; \
        printf("%c: string_replace(%s, %c, %c) == %s\n", _r, #orig, from, to, #expect); \
        if (_r != 0) ++failed; \
    } while (0);

int main() {
    TEST("a b_c", ' ', '_', "a_b_c");
    TEST("a b c", ' ', '_', "a_b_c");
    TEST("aaaaa", 'a', 'b', "bbbbb");
    TEST("",      ' ', '_', "");

    return failed;
}