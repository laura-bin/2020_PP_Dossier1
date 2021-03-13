#pragma once
/** *******************************************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Generic linked list
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 *********************************************************************************************************************/

/* Generic linked list structure */
struct node {
    void *data;
    struct node *previous;
    struct node *next;
};

/**
 * Appends a given item to a given linked list
 *
 * @param list: linked list pointer
 * @param item: item pointer
 *
 * @return the pointer of the last node of the list (new item)
 */
struct node *append_item(struct node *list, void *item);

/**
 * Frees a linked list
 *
 * @param head: pointer of the first node of the list
 * @param free_data: free data boolean
 */
void free_list(struct node *head, int free_data);
