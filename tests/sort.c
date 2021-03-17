#include <assert.h>
#include <stdio.h>

// #include "utils/sort.h"
#include "../src/utils/sort.c" // just testing private functions...

int compare_ints(const int* a, const int* b) {
    return *a - *b;
}

#define ELEMS 8
#define ASSERT(x) do { \
            printf(#x": "); \
            fflush(stdout); \
            assert(x); \
            printf("ok\n"); \
        } while (0)

int main() {
    int unsorted_array[ELEMS] = { 3, 2, 6, 1, 5, 10, 5, 9 };
    int sorted_array[ELEMS]   = { 1, 2, 3, 5, 5, 6, 9, 10 };

    ASSERT(*((int*)_elem(unsorted_array, sizeof(int), 0)) == 3);
    ASSERT(*((int*)_elem(unsorted_array, sizeof(int), 1)) == 2);
    ASSERT(*((int*)_elem(unsorted_array, sizeof(int), 2)) == 6);

    char buffer[sizeof(int)];
    _swap(
        _elem(unsorted_array, sizeof(int), 2),
        _elem(unsorted_array, sizeof(int), 3),
        sizeof(int), buffer);

    ASSERT(unsorted_array[2] == 1);
    ASSERT(unsorted_array[3] == 6);

    quick_sort(
        unsorted_array,
        ELEMS - 1,
        sizeof(int),
        &compare_ints);

    printf("%d elements\n", ELEMS);
    for (size_t i = 0; i < ELEMS; ++i) {
        ASSERT(unsorted_array[i] == sorted_array[i]);
    }

    return 0;
}