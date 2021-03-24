/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Test linked list and sort
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "utils/linked_list.h"
#include "search/search_result.h"

#include <assert.h>
#include <stdio.h>

#define ELEMS 5

int compare_ints(const void* a, const void* b) {
    const int *a_int = *(int**) a, *b_int = *(int**) b;
    return *a_int - *b_int;
}

int main() {
    struct node *head = NULL, *node = NULL;
    unsigned i, failures = 0;
    int numbers[ELEMS] = { 3, 5, 1, 6, 10 };
    int sorted_numbers[ELEMS] = { 1, 3, 5, 6, 10 };

    for (i = 0; i < ELEMS; ++i) {
        node = append_item(node, &numbers[i]);
        if (!head) head = node;
    }

    struct search_result r = {
        .head = head,
        .tail = node,
        .result_count = ELEMS,
    };

    sort_linked_list(&r, &compare_ints);

    for (node = r.head, i = 0; i < ELEMS && node; ++i, node = node->next) {
        printf("[%u] %d == %d: ", i, sorted_numbers[i], *(int*) node->data);
        if ((*(int*)node->data) == sorted_numbers[i]) {
            printf("v\n");
        } else {
            printf("x\n");
            ++failures;
        }
    }

    assert(i == ELEMS);
    assert(node == NULL);

    free_list(r.head, 0);

    return failures;
}