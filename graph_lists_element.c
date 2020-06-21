#include "memory.h"
#include "lists_element.h"
#include "graph_lists.h"

ListSElement* lists_element_new() {
    ListSElement* ep;
    NEW(ep, 1);
    return ep;
}

void lists_element_delete(ListSElement* const element_p) {
    free(element_p);
}

void lists_element_print(const ListSElement* const element_p, FILE* const fp) {
    fprintf(fp, "%ld %f", element_p->j + 1, element_p->cost);
}

bool lists_element_read(ListSElement* element_p) {
    int j1;
    scanf("%d", &j1);
    if (j1 == -1) {
        return false;
    }
    element_p->j = (size_t)(j1-1);
    scanf("%lf", &element_p->cost);
    return true;
}

bool lists_element_is_equal(const ListSElement* const a, const ListSElement* const b) {
    return a->j == b->j;
}

void lists_element_clone(const ListSElement* const src, ListSElement* const dst) {
    dst->j = src->j;
    dst->cost = src->cost;
}
