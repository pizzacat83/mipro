#include <malloc.h>
#include "./heap_element.h"
#include "./element_double_size_t.h"

void heap_element_delete(HeapElement* const ep) {
    free(ep);
}

int heap_element_cmp(const HeapElement* const x, const HeapElement* const y) {
    if (x->x < y->x) return -1;
    if (x->x > y->x) return 1;
    if (x->n < y->n) return -1;
    if (x->n > y->n) return 1;
    return 0;
}

int heap_element_revcmp(const HeapElement* const x, const HeapElement* const y) {
   return -heap_element_cmp(x, y);
}
