#ifndef H_GRAPH_LISTS_ELEMENT
#define H_GRAPH_LISTS_ELEMENT

#include <stddef.h>
#include "lists.h"

struct ListSElement {
    size_t j;
    double cost;
};

void lists_element_clone(const ListSElement* const src, ListSElement* const dst);

#endif
