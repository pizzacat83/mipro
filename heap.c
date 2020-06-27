#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "./memory.h"
#include "./heap.h"

Heap create_empty(size_t max_size, CmpFunc cmp) {
    Heap heap;
    heap.max_size = max_size;
    heap.size = 0;
    NEW(heap.tree, max_size);
    heap.cmp = cmp;
    return heap;
}

static size_t argmin(Heap heap, size_t i, size_t j) {
    return heap.cmp(heap.tree[i], heap.tree[j]) == -1 ? i : j;
}

static void swap_node(Heap* const heap_p, size_t i, size_t j) {
    HeapElement* tmp = heap_p->tree[i];
    heap_p->tree[i] = heap_p->tree[j];
    heap_p->tree[j] = tmp;
}

static size_t lchild(size_t parent) {
    return 2 * (parent+1) - 1;
}

static size_t rchild(size_t parent) {
    return 2 * (parent+1) + 1 - 1;
}

static size_t parent(size_t child) {
    return (child + 1) / 2 - 1;
}

static size_t is_top(size_t node) {
    return node == 0;
}

static void heapify(Heap* const heap_p, size_t parent) {
    size_t new_parent = parent;
    size_t l = lchild(parent);
    size_t r = rchild(parent);
    if (l < heap_p->size) {
        new_parent = argmin(*heap_p, new_parent, l);
    }
    if (r < heap_p->size) {
        new_parent = argmin(*heap_p, new_parent, r);
    }
    if (new_parent == parent) {
        // すでにheap
        return;
    }
    swap_node(heap_p, parent, new_parent);
    heapify(heap_p, new_parent);
}

Heap create_from(HeapElement** array, size_t size, size_t max_size, CmpFunc cmp) {
    if (max_size < size) {
        fprintf(stderr, "Warning(heap_create_from): Heap max_size is smaller than size. Extending max_size to size.");
        max_size = size;
    }
    Heap heap;
    heap.tree = array;
    heap.cmp = cmp;
    heap.max_size = max_size;
    heap.size = size;
    for (int i = (int)(size/2); i >= 0; --i) { // size/2 以下は葉っぱなのでheapify不要
        heapify(&heap, (size_t)i);
    }
    return heap;
}

const HeapElement* top(Heap heap) {
    if (heap.size == 0) {
        return NULL;
    }
    return heap.tree[0];
}

void pop(Heap* const heap_p) {
    heap_element_delete(heap_p->tree[0]);
    heap_p->tree[0] = heap_p->tree[heap_p->size-1];
    --heap_p->size;
    heapify(heap_p, 0);
}

void clear(Heap* const heap_p) {
    for (size_t i = 0; i < heap_p->size; ++i) {
        heap_element_delete(heap_p->tree[i]);
    }
    free(heap_p->tree);
    heap_p->tree = NULL;
    heap_p->size = 0;
    heap_p->max_size = 0;
}

static void expand(Heap* const heap_p, size_t max_size) {
    if (heap_p->max_size > max_size) {
        fprintf(stderr, "Attempt to shrink heap. Ignoring.\n");
        return;
    }
    RENEW(heap_p->tree, max_size);
    heap_p->max_size = max_size;
}

void insert(Heap* const heap_p, HeapElement* const element_p) {
    if (heap_p->max_size == heap_p->size) {
        expand(heap_p, heap_p->max_size * 2);
    }
    heap_p->tree[heap_p->size] = element_p;
    size_t child = heap_p->size;
    while (!is_top(child)) {
        size_t p = parent(child);
        if (heap_p->cmp(heap_p->tree[p], heap_p->tree[child]) == 1) {
            swap_node(heap_p, p, child);
            child = p;
        } else {
            break;
        }
    }
    ++heap_p->size;
}

bool empty(Heap heap) {
    return heap.size == 0;
}

HeapFuncs HEAP = {create_empty, create_from, clear, top, pop, insert, empty};
