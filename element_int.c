#include <malloc.h>
#include "./heap_element.h"
#include "./element_int.h"

void element_delete(Element* const ep) {
    free(ep);
}

int element_cmp(const Element* const x, const Element* const y) {
    if (x->value < y->value) return -1;
    if (x->value > y->value) return 1;
    return 0;
}

int element_revcmp(const Element* const x, const Element* const y) {
   return -element_cmp(x, y);
}
