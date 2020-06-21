#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#include <stdio.h>
#include <math.h>
#include "./memory.h"
#include "./heap.h"
#include "./element_double_size_t.h"
#include "graph_lists.h"
#include "graph_lists_element.h"

int main() {
    GraphListS graph = graph_lists_read();

    Heap heap = HEAP.create_empty(2, heap_element_cmp);
    HeapElement* ep;
    NEW(ep, 1);
    ep->n = 0;
    ep->x = 0;
    HEAP.insert(&heap, ep);

    double* d;
    NEW(d, graph.vertex_num);
    for (size_t i = 0; i < graph.vertex_num; ++i) {
        d[i] = INFINITY;
    }
    d[0] = 0;

    while (!HEAP.empty(&heap)) {
        const HeapElement* top = HEAP.top(heap);
        size_t v = top->n;
        if (top->x > d[v]) {
            // old distance
            HEAP.pop(&heap);
            continue;
        }
        LISTS_FOREACH(graph.edges[v], node_p) {
            ListSElement* e = node_p->value;
            if (d[e->j] > d[v] + e->cost) {
                fprintf(stderr, "update %ld: %lf -> %lf by %ld\n", e->j + 1, d[e->j], d[v] + e->cost, v + 1);
                d[e->j] = d[v] + e->cost;
                HeapElement* ep;
                NEW(ep, 1);
                ep->n = e->j;
                ep->x = d[e->j];
                HEAP.insert(&heap, ep);
            }
        }
        HEAP.pop(&heap);
    }

    for (size_t i = 0; i < graph.vertex_num; ++i) {
        printf("%ld %f\n", i + 1, d[i]);
    }

    graph_lists_clear(&graph);
    HEAP.clear(&heap);
    free(d);
    return 0;
}
