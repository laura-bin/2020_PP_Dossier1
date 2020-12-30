/** *******************************************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Generic linked list
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 *********************************************************************************************************************/

#include <stdlib.h>

#include "utils/linked_list.h"

struct node *append_item(struct node *list, void *item) {
    struct node *new_node = malloc(sizeof(struct node));

    // place the pointer to the last node of the list
    if (list != NULL) while (list->next != NULL) list = list->next;

    // fill the new node
    new_node->data = item;
    new_node->previous = list;
    new_node->next = NULL;

    // add the new node at the end of the list
    if (list != NULL) list->next = new_node;

    return new_node;
}

void free_list(struct node *head, int free_data) {
    struct node *next_node;

    while (head) {
        // save next node pointer
        next_node = head->next;

        // free the data
        if (free_data) {
            free(head->data);
        }

        // free the node
        free(head);

        // iterate on next node
        head = next_node;
    }
}