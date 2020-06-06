#include <malloc.h>
#include "./heap_element.h"
#include "./heap_element_int.h"

void heap_element_delete(HeapElement* const ep) {
    free(ep);
}

int cmp(const HeapElement* const x, const HeapElement* const y) {
    if (x->value < y->value) return -1;
    if (x->value > y->value) return 1;
    return 0;
}

int revcmp(const HeapElement* const x, const HeapElement* const y) {
   return -cmp(x, y);
}
