#ifndef H_HEAP
#define H_HEAP

#include <stddef.h>

#include "./heap_element.h"

typedef struct {
    size_t max_size;
    size_t size;
    Element** tree;
    CmpFunc cmp;
} Heap;

Heap heap_create_empty(size_t max_size, CmpFunc cmp);

Heap heap_create_from(Element** array, size_t size, size_t max_size, CmpFunc cmp);

void heap_clear(Heap* const heap_p);

const Element* heap_top(Heap heap);

void heap_pop(Heap* const heap_p);


#endif
