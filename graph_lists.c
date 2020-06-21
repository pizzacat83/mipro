#include "graph_lists.h"

GraphListS graph_empty_create(size_t vertex_num, size_t edge_num) {
    GraphListS graph;
    graph.vertex_num = vertex_num;
    NEW(graph.edges, vertex_num);
    for (size_t i = 0; i < vertex_num; ++i) {
        graph.edges[i] = lists_create_empty();
    }
    graph.edge_num = edge_num;
    return graph;
}

void graph_lists_clear(GraphListS* const graph_p) {
    for (size_t i = 0; i < graph_p->vertex_num; ++i) {
        lists_clear(&graph_p->edges[i]);
    }
    free(graph_p->edges);
}

GraphListS graph_lists_read() {
    size_t vertex_num, edge_num;
    scanf("%ld %ld", &vertex_num, &edge_num);
    GraphListS graph = graph_empty_create(vertex_num, edge_num);
    for (size_t i = 0; i < vertex_num; ++i) {
        lists_read(&graph.edges[i]);
    }
    return graph;
}

void graph_lists_print(GraphListS graph, FILE* fp) {
    fprintf(fp, "%ld %ld\n", graph.vertex_num, graph.edge_num);
    for (size_t i = 0; i < graph.vertex_num; ++i) {
        lists_print(graph.edges[i], fp);
    }
}

GraphListS graph_lists_transpose(GraphListS graph) {
    GraphListS graphT = graph_empty_create(graph.vertex_num, graph.edge_num);
    for (size_t i = 0; i < graph.vertex_num; ++i) {
        LISTS_FOREACH(graph.edges[i], node_p) {
            ListSElement* ep = element_new();
            ep->cost = node_p->value->cost;
            ep->j = i;
            lists_push_back(&graphT.edges[node_p->value->j], ep);
        }
    }
    return graphT;
}
