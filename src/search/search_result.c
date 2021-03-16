/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Sort search result list
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdlib.h>

#include "search/search_result.h"
#include "utils/sort.h"

void sort_linked_list(struct search_result *results, int (*compare)(const void *, const void *)) {
    void **sorted_array;                    // array containing the linked list data pointers
    void **current;                         // current element of the sorted array (for iteration)
    struct node *current_node;              // current node of the linked list (for iteration)
    struct node *head = results->head;      // results linked list head backup
    unsigned i;

    // sorted array initialization
    sorted_array = malloc(results->result_count * sizeof(void *));
    current = sorted_array;
    current_node = results->head;

    // copy the data pointers into the array to sort
    while (current_node) {
        *current = current_node->data;
        current++;
        current_node = current_node->next;
    }

    // sort the array
    quick_sort(sorted_array, results->result_count, sizeof(void *), compare);

    // reassigning the sorted results
    results->head = NULL;
    results->tail = NULL;
    for (i = 0; i < results->result_count; i++) {
        results->tail = append_item(results->tail, sorted_array[i]);
        if (results->head == NULL) results->head = results->tail;
    }

    // free the old linked list
    free_list(head, 0);
}