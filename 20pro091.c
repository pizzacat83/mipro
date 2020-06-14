#pragma GCC diagnostic ignored "-Wmissing-prototypes"

#include "memory.h"
#include "lists.h"
#include "graph_lists.h"

typedef enum {
    NOTVISITED,
    VISITING,
    VISITED
} Status;

int dfs1_rec(GraphListS graph, size_t i, int time, Status* const statuses, int* pre, int* post) {
    statuses[i] = VISITING;
    pre[i] = time;
    LISTS_FOREACH(graph.edges[i], node_p) {
        size_t j = node_p->value->j;
        if (statuses[j] == NOTVISITED) {
            time = dfs1_rec(graph, j, time + 1, statuses, pre, post);
        }
    }
    statuses[i] = VISITED;
    post[i] = time + 1;
    return post[i];
}

void dfs1(GraphListS graph, int* pre, int* post) {
    Status* statuses;
    NEW(statuses, graph.vertex_num);
    for (size_t i = 0; i < graph.vertex_num; ++i) {
        statuses[i] = NOTVISITED;
    }
    int time = 0;
    for (size_t i = 0; i < graph.vertex_num; ++i) {
        if (statuses[i] == NOTVISITED) {
            time = dfs1_rec(graph, i, time + 1, statuses, pre, post);
        }
    }

    free(statuses);
}

int main() {
    GraphListS graph = graph_lists_read();

    int* pre;
    int* post;
    NEW(pre, graph.vertex_num);
    NEW(post, graph.vertex_num);

    for (size_t i = 0; i < graph.vertex_num; ++i) {
        pre[i] = -1;
        post[i] = -1;
    }

    dfs1(graph, pre, post);

    for (size_t i = 0; i < graph.vertex_num; ++i) {
        printf("%ld: %d %d\n", i, pre[i], post[i]);
    }


    free(pre);
    free(post);
    graph_lists_clear(&graph);
    return 0;
}
