#pragma once
/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Tests helpers
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/catalog.h"

#include <stdio.h>
#include <stdlib.h>

#define ASSERT_EQUALS(expect, value) do {\
        printf("    " #expect " == " #value ": %u == %u: ", value, expect); \
        fflush(stdout); \
        if (expect == value) { \
            printf("v\n"); \
        } else { \
            failures++; \
            printf("x\n"); \
        } \
    } while (0)

#define ASSERT_ARRAY_EQUALS(expect, actual, size) do { \
        for (size_t __i = 0; __i < size; ++__i) { \
            printf("    " #expect "[%lu] (%d) == " #actual "[%lu] (%d): ", __i, expect[__i], __i, actual[__i]); \
            fflush(stdout); \
            if (expect[__i] == actual[__i]) { \
                printf("v\n"); \
            } else { \
                failures++; \
                printf("x\n"); \
            } \
        } \
    } while (0)

int compare_unsigned(const void *a, const void *b) {
    const unsigned *left = a, *right = b;
    if (*left == *right) {
        return 0;
    } else if (*left < *right) {
        return -1;
    } else {
        return 1;
    }
}

unsigned get_id(enum table table, void *data) {
    switch (table) {
    case COUNTRY: return ((struct country*) data)->id;
    case JOB: return ((struct job*) data)->id;
    case INDUSTRY: return ((struct industry*) data)->id;
    case GROUP: return ((struct group*) data)->id;
    case COMPANY: return ((struct company*) data)->id;
    case PERSON: return ((struct person*) data)->id;
    case TAB_COUNT: break;
    }
    fprintf(stderr, "invalid table: %d\n", table);
    exit(-1);
}

void sort_ids(enum table table, struct node *node, unsigned *out_sorted, unsigned count) {
    unsigned *first = out_sorted;
    while (node) {
        *out_sorted = get_id(table, node->data);

        node = node->next;
        out_sorted++;
    }
    qsort(first, count, sizeof(unsigned), &compare_unsigned);
}
