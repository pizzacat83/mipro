#include <stdio.h>
#include <math.h>
#include "./memory.h"
#include "./heap.h"
#include "./element_double_size_t.h"
#include "graph_lists.h"
#include "graph_lists_element.h"
#include "dijkstra.h"

// 格納先は呼び出し元が確保・解放してください
void dijkstra(GraphListS graph, size_t start, double* d) {
    for (size_t i = 0; i < graph.vertex_num; ++i) {
        d[i] = INFINITY;
    }
    d[start] = 0;

    Heap heap = HEAP.create_empty(graph.edge_num, heap_element_cmp);
    HeapElement* ep;
    NEW(ep, 1);
    ep->n = start;
    ep->x = 0;
    HEAP.insert(&heap, ep);

    while (!HEAP.empty(heap)) {
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

    HEAP.clear(&heap);
}
