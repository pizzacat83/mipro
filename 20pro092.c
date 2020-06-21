#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#include <stdio.h>
#include <stddef.h>
#include "lists.h"
#include "graph_lists.h"
#include "graph_lists_element.h"

int main() {
    GraphListS graph = graph_lists_read();
    size_t s, t;
    scanf("%ld %ld", &s, &t);
    --s;
    --t;
    ListS queue = lists_create_empty();
    ListSElement* ep;
    NEW(ep, 1);
    ep->j = s;
    ep->cost = 1;
    lists_push_back(&queue, ep);

    int* d;
    NEW(d, graph.vertex_num);
    for(size_t i = 0; i < graph.vertex_num; ++i) {
        d[i] = -1;
    }
    d[s] = 0;

    while(queue.head != NULL) {
        size_t v = queue.head->value->j;
        lists_erase_front(&queue);
        LISTS_FOREACH(graph.edges[v], edge_p) {
            size_t u = edge_p->value->j;
            if (d[u] == -1) {
                d[u] = d[v] + 1;
                ListSElement* ep;
                NEW(ep, 1);
                ep->j = u;
                ep->cost = 1;
                lists_push_back(&queue, ep);
            }
        }
    }
    printf("%d\n", d[t]);

    lists_clear(&queue);
    graph_lists_clear(&graph);
    free(d);
}
