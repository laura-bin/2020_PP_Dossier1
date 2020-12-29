/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database file searches by index:
 *  - search people by company id
 *  - search people by lastname prefix
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdlib.h>

#include "search/index_search.h"

void *search_people_by_company_id(struct db *db) {
    void *r = NULL;
    return r;
}

void *search_people_by_lastname(struct db *db) {
    void *r = NULL;
    return r;
}


// int search_people_by_start_lastname(struct db *db) {
    // char searched[MAX_LEN];         // substring searched
    // unsigned i;                     // record index
    // struct person *found;           // record found
    // struct node *head = NULL;       // linked list head
    // struct node *cur_node = NULL;   // linked list current node
    // unsigned results = 0;           // number of records found

    // printf("Enter the substring searched: ");
    // get_text_input(searched, MAX_LEN);

    // unsigned offset = 0;

    // while (offset) {
    //     fseek(db->dat_file, offset, SEEK_SET);
    //     fread(&index, 1, sizeof(struct person_by_lastname), db->dat_file);

    //     // if (compare...)

    //     // read
    //     fseek(db->dat_file, index.offset, SEEK_SET);
    //     fread(&found, 1, sizeof(struct person), db->dat_file);
        
    //     // add to linked list -> déjà triée puisque index sur le nom


    // }

    // for (i = 0; i < db->header.n_table_rec[PERSON]; i++) {
    //     found = NULL; // comparer le nom de l'index à searched
    //     if (found != NULL) {
    //         cur_node = append_item(cur_node, found);
    //         if (head == NULL) head = cur_node;
    //         results++;
    //     }
    // }

    // if (! results) {
    //     puts("No result found");
    // } else {
    //     paginate(results, head, table->print, table->print_header);
    //     free_list(head);
    // }

//     return 0;
// }
