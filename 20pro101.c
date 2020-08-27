#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#include <stdio.h>
#include <math.h>
#include "./memory.h"
#include "./heap.h"
#include "./element_double_size_t.h"
#include "graph_lists.h"
#include "graph_lists_element.h"
#include "dijkstra.h"

int main() {
    GraphListS graph = graph_lists_read();

    double* d;
    NEW(d, graph.vertex_num);

    dijkstra(graph, 0, d);

    for (size_t i = 0; i < graph.vertex_num; ++i) {
        printf("%lu %f\n", i + 1, d[i]);
    }

    graph_lists_clear(&graph);
    free(d);
    return 0;
}
