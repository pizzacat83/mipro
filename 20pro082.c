#pragma GCC diagnostic ignored "-Wmissing-prototypes"

#include "memory.h"
#include "lists.h"
#include "graph_lists.h"

typedef enum {
    NOTVISITED,
    VISITING,
    VISITED
} Status;

void dfs_rec(GraphListS graph, size_t i, int* const res, Status* const statuses) {
    statuses[i] = VISITING;
    LISTS_FOREACH(graph.edges[i], node_p) {
        size_t j = node_p->value->j;
        if (statuses[j] == NOTVISITED) {
            res[j] = (int)i + 1;
            dfs_rec(graph, j, res, statuses);
        }
    }
    statuses[i] = VISITED;
}

void dfs(GraphListS graph, int* const res) {
    Status* statuses;
    NEW(statuses, graph.vertex_num);
    for (size_t i = 0; i < graph.vertex_num; ++i) {
        statuses[i] = NOTVISITED;
    }

    for (size_t i = 0; i < graph.vertex_num; ++i) {
        if (statuses[i] == NOTVISITED) {
            dfs_rec(graph, i, res, statuses);
        }
    }

    free(statuses);
}

int main() {
    GraphListS graph = graph_lists_read();

    int* res;
    NEW(res, graph.vertex_num);
    for (size_t i = 0; i < graph.vertex_num; ++i) {
        res[i] = -1;
    }

    dfs(graph, res);

    for (size_t i = 0; i < graph.vertex_num; ++i) {
        printf("%d ", res[i]);
    }

    free(res);
    graph_lists_clear(&graph);
    return 0;
}
