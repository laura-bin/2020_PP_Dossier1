#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Search result structure returned by the search functions
 * Sort search result list
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "utils/linked_list.h"

/* Search result structure */
struct search_result {
    unsigned result_count;  // number of results found
    struct node *head;      // first result of the linked list
    struct node *tail;      // last result of the linked list
};

/**
 * Sorts a given results linked list (the list is modified by the sorting)
 * 
 * @param results: linked list to sort
 * @param compare: comparison function on which to base the sorting
 */
void sort_linked_list(struct search_result *results, int (*compare)(const void *, const void *));
