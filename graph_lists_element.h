#ifndef H_GRAPH_LISTS_ELEMENT
#define H_GRAPH_LISTS_ELEMENT

#include <stddef.h>
#include "lists.h"

struct Element {
    size_t j;
    int cost;
};

void element_clone(const Element* const src, Element* const dst);

#endif
