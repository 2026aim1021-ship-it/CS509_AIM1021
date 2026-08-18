#include "kruskal.h"
struct DSU{
    vector<int> parent;

    DSU(int n){
        parent.resize(n);
        for(int i=0;i<n;i++)
            parent[i] = i;
    }

    int find(int x){
        while(parent[x]!=x){
            parent[x] = parent[parent[x]];
            x = parent[x];
        }

        return x;
    }

    bool unite(int a,int b){
        a = find(a);
        b = find(b);

        if (a==b)
            return false;

        parent[b] = a;
        return true;
    }
};

mst_result kruskalMST(const csr_graph *graph){
    int V = graph->V;
    vector<mst_edge> edges;

    for(int u=0;u<V;u++){
        for(int i=graph->row_ptr[u];i<graph->row_ptr[u+1];i++){
            int v = graph->col_idx[i];

            if(u<v){
                edges.push_back({u,v,graph->values[i]});
            }
        }
    }

    sort(edges.begin(),edges.end(),[](const mst_edge &a,const mst_edge &b){ return a.w<b.w;});

    DSU dsu(V);
    mst_result result;

    for(auto e:edges){
        if(dsu.unite(e.u,e.v)){
            result.edges.push_back(e);
            result.totalWeight += e.w;
        }

        if((int)result.edges.size()==V-1){
            break;
        }
    }

    if(V>0 && (int)result.edges.size()!=V-1){
        result.valid = false;
    }

    return result;
}
