#ifndef H_HEAP
#define H_HEAP

#include <stddef.h>
#include "./heap_element.h"

typedef struct {
    size_t max_size;
    size_t size;
    HeapElement** tree;
    CmpFunc cmp;
} Heap;

typedef struct {
    Heap (*create_empty)(size_t max_size, CmpFunc cmp);
    Heap (*create_from)(HeapElement** array, size_t size, size_t max_size, CmpFunc cmp);
    void (*clear)(Heap* const heap_p);
    const HeapElement* (*top)(Heap heap);
    void (*pop)(Heap* const heap_p);
    void (*insert)(Heap* const heap_p, HeapElement* const element_p);
} HeapFuncs;

extern HeapFuncs HEAP;

#endif
