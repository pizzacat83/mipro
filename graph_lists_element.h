#ifndef H_GRAPH_LISTS_ELEMENT
#define H_GRAPH_LISTS_ELEMENT

#include <stddef.h>
#include "lists.h"

struct ListSElement {
    size_t j;
    int cost;
};

void element_clone(const ListSElement* const src, ListSElement* const dst);

#endif
