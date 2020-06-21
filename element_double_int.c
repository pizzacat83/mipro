#include <malloc.h>
#include "./heap_element.h"
#include "./element_double_int.h"

void element_delete(HeapElement* const ep) {
    free(ep);
}

int element_cmp(const HeapElement* const x, const HeapElement* const y) {
    if (x->x < y->x) return -1;
    if (x->x > y->x) return 1;
    if (x->n < y->n) return -1;
    if (x->n > y->n) return 1;
    return 0;
}

int element_revcmp(const HeapElement* const x, const HeapElement* const y) {
   return -element_cmp(x, y);
}
