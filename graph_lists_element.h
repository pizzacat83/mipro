#ifndef H_ELEMENT_SLIST_GRAPH
#define H_ELEMENT_SLIST_GRAPH

#include <stddef.h>
#include "lists.h"

struct Element {
    size_t j;
    int cost;
};

void element_clone(const Element* const src, Element* const dst);

#endif
