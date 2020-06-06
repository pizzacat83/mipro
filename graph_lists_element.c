#include "memory.h"
#include "lists_element.h"
#include "graph_lists.h"

Element* element_new() {
    Element* ep;
    NEW(ep, 1);
    return ep;
}

void element_delete(Element* const element_p) {
    free(element_p);
}

void element_print(const Element* const element_p, FILE* const fp) {
    fprintf(fp, "%ld %d", element_p->j + 1, element_p->cost);
}

bool element_read(Element* element_p) {
    int j1;
    scanf("%d", &j1);
    if (j1 == -1) {
        return false;
    }
    element_p->j = (size_t)(j1-1);
    scanf("%d", &element_p->cost);
    return true;
}

bool element_is_equal(const Element* const a, const Element* const b) {
    return a->cost == b->cost && a->j == b->j;
}

void element_clone(const Element* const src, Element* const dst) {
    dst->j = src->j;
    dst->cost = src->cost;
}
