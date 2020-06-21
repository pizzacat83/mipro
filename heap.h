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

typedef struct {
    Heap (*create_empty)(size_t max_size, CmpFunc cmp);
    Heap (*create_from)(Element** array, size_t size, size_t max_size, CmpFunc cmp);
    void (*clear)(Heap* const heap_p);
    const Element* (*top)(Heap heap);
    void (*pop)(Heap* const heap_p);
} HeapFuncs;

extern HeapFuncs HEAP;

#endif
