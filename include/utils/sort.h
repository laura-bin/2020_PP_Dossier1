#pragma once
/** *******************************************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 * 
 * Sort functions:
 *  - quick sort
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 *********************************************************************************************************************/

/**
 * Quick sort algorithm
 * 
 * @param ptr: pointer of the array to sort
 * @param count: number of elements to sort
 * @param size: size of the elements
 * @param comp: comparison function
 */
void quick_sort(void *ptr, size_t count, size_t size, int (*comp)(const void *, const void *));
