#include "graph_lists.h"

int main() {
    GraphListS graph = graph_lists_read();
    GraphListS graphT = graph_lists_transpose(graph);
    graph_lists_print(graphT, stdout);
    graph_lists_clear(&graph);
    graph_lists_clear(&graphT);
    return 0;
}
