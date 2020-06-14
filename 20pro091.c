#pragma GCC diagnostic ignored "-Wmissing-prototypes"

#include "memory.h"
#include "lists.h"
#include "graph_lists.h"

typedef enum {
    NOTVISITED,
    VISITING,
    VISITED
} Status;

size_t dfs1_rec(GraphListS graph, size_t i, size_t time, Status* const statuses, size_t* const pre, size_t* const post) {
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

void dfs1(GraphListS graph, size_t* const pre, size_t* const post) {
    Status* statuses;
    NEW(statuses, graph.vertex_num);
    for (size_t i = 0; i < graph.vertex_num; ++i) {
        statuses[i] = NOTVISITED;
    }
    size_t time = 0;
    for (size_t i = 0; i < graph.vertex_num; ++i) {
        if (statuses[i] == NOTVISITED) {
            time = dfs1_rec(graph, i, time + 1, statuses, pre, post);
        }
    }

    free(statuses);
}

void dfs2_rec(GraphListS graph, size_t i, int* parents, Status* const statuses) {
    statuses[i] = VISITING;
    LISTS_FOREACH(graph.edges[i], node_p) {
        size_t j = node_p->value->j;
        if (statuses[j] == NOTVISITED) {
            parents[j] = (int)i;
            dfs2_rec(graph, j, parents, statuses);
        }
    }
    statuses[i] = VISITED;
}

void dfs2(GraphListS graph, size_t* ord, int* parents) {
    Status* statuses;
    NEW(statuses, graph.vertex_num);
    for (size_t i = 0; i < graph.vertex_num; ++i) {
        statuses[i] = NOTVISITED;
    }

    for (size_t i = 0; i < graph.vertex_num; ++i) {
        size_t v = ord[i];
        if (statuses[v] == NOTVISITED) {
            parents[v] = -1;
            dfs2_rec(graph, v, parents, statuses);
        }
    }
    free(statuses);
}

void rev_sort_by_post(size_t * const ord, size_t V, const size_t* const post) {
    // TODO: heap?
    int* ord_tmp;
    NEW(ord_tmp, V*2 + 1);
    for(size_t i = 0; i < V*2 + 1; ++i) {
        ord_tmp[i] = -1;
    }
    for(size_t v = 0; v < V; ++v) {
        ord_tmp[post[v]] = (int)v;
    }
    size_t k = 0;
    for(size_t i_ = 0; i_ < V * 2 + 1; ++i_) {
        size_t i = V*2 - i_;
        if (ord_tmp[i] != -1) {
            ord[k] = (size_t)(ord_tmp[i]);
            ++k;
        }
    }
    free(ord_tmp);
}

int main() {
    GraphListS graph = graph_lists_read();

    size_t* pre;
    size_t* post;
    NEW(pre, graph.vertex_num);
    NEW(post, graph.vertex_num);

    dfs1(graph, pre, post);

    size_t* ord;
    NEW(ord, graph.vertex_num);
    rev_sort_by_post(ord, graph.vertex_num, post);
    
    int* parents;
    NEW(parents, graph.vertex_num);

    GraphListS graphT = graph_lists_transpose(graph);

    dfs2(graphT, ord, parents);

    for(size_t i = 0; i < graph.vertex_num; ++i) {
        printf("%d ", parents[i] == -1 ? -1 : parents[i] + 1);
    }
    printf("\n");

    free(pre);
    free(post);
    free(parents);
    free(ord);
    graph_lists_clear(&graph);
    graph_lists_clear(&graphT);
    return 0;
}
