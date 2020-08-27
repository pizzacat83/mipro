#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#include <stdio.h>
#include <math.h>
#include "./memory.h"
#include "./heap.h"
#include "./element_double_size_t.h"
#include "graph_lists.h"
#include "graph_lists_element.h"

void prim(GraphListS graph, size_t start, size_t* parents) {
    bool* used;
    NEW(used, graph.vertex_num);
    double* min_cost;
    NEW(min_cost, graph.vertex_num);
    for (size_t i = 0; i < graph.vertex_num; ++i) {
        used[i] = false;
        min_cost[i] = INFINITY;
    }
    min_cost[start] = 0;
    parents[start] = start;

    Heap heap = HEAP.create_empty(graph.edge_num, heap_element_cmp);
    HeapElement* ep;
    NEW(ep, 1);
    ep->n = start;
    ep->x = 0;
    HEAP.insert(&heap, ep);

    size_t used_count = 0;
    while (used_count < graph.vertex_num) {
        if (HEAP.empty(heap)) {
            for (size_t i = 0; i < graph.vertex_num; ++i) {
                if (used[i]) {
                    fprintf(stderr, "%lu ", i + 1);
                }
            }
            fprintf(stderr, "\n");
        }
        const HeapElement* top = HEAP.top(heap);
        size_t v = top->n;
        if (used[v] || min_cost[v] < top->x) {
            // top is outdated
            HEAP.pop(&heap);
            continue;
        }
        HEAP.pop(&heap);
        used[v] = true;
        min_cost[v] = 0;
        ++used_count;
        LISTS_FOREACH(graph.edges[v], node_p) {
            ListSElement* ep = node_p->value;
            if (!used[ep->j] && min_cost[ep->j] > ep->cost) {
                parents[ep->j] = v;
                min_cost[ep->j] = ep->cost;
                HeapElement* t;
                NEW(t, 1);
                t->n = ep->j;
                t->x = min_cost[ep->j];
                HEAP.insert(&heap, t);
            }
        }

    }
    HEAP.clear(&heap);
    free(used);
    free(min_cost);
}

int main() {
    GraphListS graph = graph_lists_read();
    GraphListS graph2 = graph_lists_nondirected(graph);
    graph_lists_clear(&graph);
    size_t* parents;
    NEW(parents, graph.vertex_num);

    prim(graph2, 0, parents);

    for (size_t i = 0; i < graph2.vertex_num; ++i) {
        printf("%lu %lu\n", i + 1, parents[i] + 1);
    }

    graph_lists_clear(&graph2);
    free(parents);
    return 0;
}
