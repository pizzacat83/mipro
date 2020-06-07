#ifndef H_GRAPH_LISTS
#define H_GRAPH_LISTS

#include <stddef.h>
#include "memory.h"
#include "graph_lists_element.h"

typedef struct {
    size_t vertex_num;
    size_t edge_num;
    ListS* edges;
} GraphListS;

GraphListS graph_empty_create(size_t vertex_num, size_t edge_num);

void graph_lists_clear(GraphListS* const graph_p);

GraphListS graph_lists_read(void);

void graph_lists_print(GraphListS graph, FILE* const fp);

GraphListS graph_lists_transpose(GraphListS graph);

#endif
