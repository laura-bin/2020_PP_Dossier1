/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Test quick sort algorithm
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <assert.h>
#include <stdio.h>

#include "utils/sort.h"

int compare_ints(const void* a, const void* b) {
    const int *a_int = a, *b_int = b;
    return *a_int - *b_int;
}

#define ELEMS 8

#define ASSERT_ARRAY_EQUALS(expect, actual, size) do { \
        for (size_t __i = 0; __i < ELEMS; ++__i) { \
            printf(#expect "[%lu] (%d) == " #actual "[%lu] (%d): ", __i, expect[__i], __i, actual[__i]); \
            fflush(stdout); \
            assert(expect[__i] == actual[__i]); \
            printf("ok\n"); \
        } \
    } while (0)

int main() {
    int unsorted_array[ELEMS] = { 3, 2, 6, 1, 5, 10, 5, 9 };
    int sorted_array[ELEMS]   = { 1, 2, 3, 5, 5, 6, 9, 10 };
    
    quick_sort(
        unsorted_array,
        ELEMS,
        sizeof(int),
        &compare_ints);

    printf("%d elements\n", ELEMS);
    ASSERT_ARRAY_EQUALS(sorted_array, unsorted_array, ELEMS);

    return 0;
}