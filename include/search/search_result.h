#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Search result structure returned by the search functions
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
