#pragma GCC diagnostic ignored "-Wmissing-prototypes"
#include <stdio.h>
#include <math.h>
#include "./memory.h"
#include "util.h"
#include "debug.h"
#include "graph_lists.h"
#include "graph_lists_element.h"
#include "dijkstra.h"
#include "memory.h"
#include "set.h"
#include "heap.h"
#include "element_double_size_t.h"

// グラフから完全グラフを作る
// d は呼び出し元が確保・解放してください
void complete_graph(GraphListS graph, double** d) {
    for(size_t i = 0; i < graph.vertex_num; ++i) {
        dijkstra(graph, i, d[i]);
    }
}

double tsp(size_t n, double* const* const d) {
    size_t N = 1ul<<(n-1);
    // dp[S][i]: 0 から S を通って i にいく
    double** dp;
    NEW(dp, N);

    for (Set S = 0; S < N; ++S) {
        NEW(dp[S], n);
        for (size_t j = 0; j < n; ++j) {
            dp[S][j] = INFINITY;
        }
    }

    for (size_t i = 1; i < n; ++i) {
        size_t iforS = i-1;
        dp[set_singleton(iforS)][i] = d[0][i];
    }

    for (Set S = 1; S < N; ++S) {
        log("S = %lu\n", S);
        for (size_t i = 1; i < n; ++i) {
            size_t iforS = i-1;
            if (!set_has(S, iforS)) {
                continue;
            }
            log("  i = %lu\n", i+1);
            Set Sexi = set_exclude(S, iforS);
            for (size_t j = 1; j < n; ++j) {
                size_t jforS = j-1;
                if (set_has(Sexi, jforS)) {
                    log("    j = %lu\n", j+1);
                    dp[S][i] = min(dp[S][i], dp[Sexi][j] + d[j][i]);
                }
            }
        }
    }

    double res = INFINITY;
    for (size_t i = 1; i < n; ++i) {
        res = min(res, dp[N-1][i] + d[i][0]);
    }

    #ifdef DEBUG
    for (Set S = 1; S < N; ++S) {
        for (size_t i = 1; i < n; ++i) {
            log("%lf ", dp[S][i]);
        }
        log("\n");
    }
    #endif
    

    for (size_t i = 0; i < N; ++i) {
        free(dp[i]);
    }

    free(dp);

    return res;
}


int main() {
    GraphListS digraph = graph_lists_read();
    GraphListS graph = graph_lists_nondirected(digraph);
    graph_lists_clear(&digraph);
    
    double** d;
    NEW(d, graph.vertex_num);
    for (size_t i = 0; i < graph.vertex_num; ++i) {
        NEW(d[i], graph.vertex_num);
    }
    complete_graph(graph, d);

    printf("%lf\n", tsp(graph.vertex_num, d));

    graph_lists_clear(&graph);
    for (size_t i = 0; i < graph.vertex_num; ++i) {
        free(d[i]);
    }
    free(d);
    return 0;
}
