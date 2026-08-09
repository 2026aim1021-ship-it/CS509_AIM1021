#include "bellmanFord.h"

bellmanFord_res bellmanFord(const csr_graph *graph,int source){
    bellmanFord_res result;
    int V = graph->V;
    result.distances.assign(V,INF);
    result.distances[source] = 0;

    for(int rnd=0;rnd<V;rnd++){
        bool changed = false;

        for(int u=0;u<V;u++){
            if (result.distances[u] == INF)
                continue;

            for(int e=graph->row_ptr[u];e<graph->row_ptr[u+1];e++){
                int v = graph->col_idx[e];
                long long w = graph->values[e];

                if (result.distances[u] + w<result.distances[v]){
                    result.distances[v] = result.distances[u] + w;
                    changed = true;
                }
            }
        }
            if (!changed)
                break;
    }

    for(int u=0;u<V;u++){
            if (result.distances[u] == INF)
                continue;

            for(int e=graph->row_ptr[u];e<graph->row_ptr[u+1];e++){
                int v = graph->col_idx[e];
                long long w = graph->values[e];

                if (result.distances[u] + w<result.distances[v]){
                    result.negativeCyc = true;
                    return result;
                }
            }
        }
    
    return result;
}