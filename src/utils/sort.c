/** *******************************************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 * 
 * Sort functions:
 *  - quick sort
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 *********************************************************************************************************************/

#include <stdlib.h>
#include <string.h>

/* PRIVATE FUNCTIONS */

/**
 * Gets element at index i
 * 
 * @param ptr: list of elements
 * @param element_size: size of the elements of the list
 * @param i: index of the element wanted
 * 
 * @return the requested element
 */
void *_elem(void *ptr, size_t element_size, size_t i) {
    return ((char *) ptr) + (i * element_size);
}

/**
 * Swaps two elements of the list
 * 
 * @param e1: first element
 * @param e2: second element
 * @param element_size: elements size
 * @param temp_buffer: temporary buffer used for swapping elements
 */
void _swap(void *e1, void *e2, size_t element_size, char *temp_buffer) {
    memcpy(temp_buffer, e1, element_size);
    memcpy(e1, e2, element_size);
    memcpy(e2, temp_buffer, element_size);
}

/**
 * Private quick sort
 * 
 * @param ptr: pointer of the array to sort
 * @param count: number of elements to sort
 * @param size: size of the elements
 * @param comp: comparison function
 * @param temp_buffer: temporary buffer used for swapping elements
 */
void _quick_sort(void *ptr, ssize_t first, ssize_t last, size_t element_size, int (*comp)(const void *, const void *), char *temp_buffer) {

// define utils macros to avoid having to repeat identical arguments
#define QSORT_ELEM(__i)         _elem(ptr, element_size, __i)
#define QSORT_COMP(__a, __b)    (*comp)(QSORT_ELEM(__a), QSORT_ELEM(__b))
#define QSORT_SWAP(__a, __b)    _swap(QSORT_ELEM(__a), QSORT_ELEM(__b), element_size, temp_buffer)

   ssize_t i, j, pivot;

    if (first >= last){
        return;
    }

    pivot = first;
    i = first;
    j = last;

    while (i < j) {
        while (QSORT_COMP(i, pivot) <= 0 && i < last) {
            i++;
        }

        while (QSORT_COMP(j, pivot) > 0) {
            j--;
        }

        if (i < j) {
            QSORT_SWAP(i, j);
        }
    }

    QSORT_SWAP(pivot, j);

    _quick_sort(ptr, first, j - 1, element_size, comp, temp_buffer);
    _quick_sort(ptr, j + 1, last, element_size, comp, temp_buffer);

// clear utils macros
#undef QSORT_SWAP
#undef QSORT_COMP
#undef QSORT_ELEM
}

/* HEADER IMPLEMENTATIONS */

void quick_sort(void *ptr, ssize_t count, size_t size, int (*comp)(const void *, const void *)) {
    char *temp_buffer = malloc(size);
    _quick_sort(ptr, 0, count, size, comp, temp_buffer);
    free(temp_buffer);
}
