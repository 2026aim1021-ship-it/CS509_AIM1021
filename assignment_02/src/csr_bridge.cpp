#include "csr_bridge.h"

csr_graph buildCSR(int V,const vector<vector<pair<int,long long>>> &adj){
    csr_graph g;
    g.V = V;
    g.row_ptr.assign(V+1,0);

    for(int u=0;u<V;u++){
        g.row_ptr[u+1] = g.row_ptr[u] + (int)adj[u].size();
    }
    g.E = g.row_ptr[V];

    g.col_idx.resize(g.E);
    g.values.resize(g.E);

    int pos=0;
    for(int u=0;u<V;u++){
        for(auto edge:adj[u]){
            g.col_idx[pos] = edge.first;
            g.values[pos] = edge.second;
            pos++;
        }
    }

    return g;
}