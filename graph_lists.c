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

// コピーを作るので，引数はfree可能です
GraphListS graph_lists_nondirected(GraphListS graph) {
    GraphListS graph2 = graph_empty_create(graph.vertex_num, graph.edge_num * 2);
    for (size_t i = 0; i < graph.vertex_num; ++i) {
        LISTS_FOREACH(graph.edges[i], node_p) {
            ListSElement* ep = node_p->value;
            ListSElement* ep1;
            NEW(ep1, 1);
            ep1->j = ep->j;
            ep1->cost = ep->cost;
            lists_push_back(&graph2.edges[i], ep1);
            ListSElement* ep2;
            NEW(ep2, 1);
            ep2->j = i;
            ep2->cost = ep->cost;
            lists_push_back(&graph2.edges[ep->j], ep2);
        }
    }
    return graph2;
}

GraphListS graph_lists_read() {
    size_t vertex_num, edge_num;
    scanf("%lu %lu", &vertex_num, &edge_num);
    GraphListS graph = graph_empty_create(vertex_num, edge_num);
    for (size_t i = 0; i < vertex_num; ++i) {
        lists_read(&graph.edges[i]);
    }
    return graph;
}

void graph_lists_print(GraphListS graph, FILE* fp) {
    fprintf(fp, "%lu %lu\n", graph.vertex_num, graph.edge_num);
    for (size_t i = 0; i < graph.vertex_num; ++i) {
        lists_print(graph.edges[i], fp);
    }
}

GraphListS graph_lists_transpose(GraphListS graph) {
    GraphListS graphT = graph_empty_create(graph.vertex_num, graph.edge_num);
    for (size_t i = 0; i < graph.vertex_num; ++i) {
        LISTS_FOREACH(graph.edges[i], node_p) {
            ListSElement* ep = lists_element_new();
            ep->cost = node_p->value->cost;
            ep->j = i;
            lists_push_back(&graphT.edges[node_p->value->j], ep);
        }
    }
    return graphT;
}
