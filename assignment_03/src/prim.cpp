#include "prim.h"
#include <bits/stdc++.h>
using namespace std;

mst_result primMST(const csr_graph *graph,int startIndex){
    int V = graph->V;
    mst_result result;

    if(V==0)
        return result;

    vector<int> parent(V,-1);
    vector<bool> visited(V,false);
    vector<long long> key(V,LLONG_MAX);

    key[startIndex] = 0;
    priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> pq;
    pq.push({0,startIndex});
    int count = 0;

    while(!pq.empty()){
        auto [w,u] = pq.top();
        pq.pop();

        if(visited[u])
            continue;

        visited[u] = true;
        count++;

        if(parent[u]!=-1){
            result.edges.push_back({parent[u],u,key[u]});
            result.totalWeight += key[u];
        }

        for(int i=graph->row_ptr[u];i<graph->row_ptr[u+1];i++){
            int v = graph->col_idx[i];
            long long w = graph->values[i];
            
            if(!visited[v] && w<key[v]){
                key[v] = w;
                parent[v] = u;
                pq.push({w,v});
            }
        }
    }

    if(count!=V)
        result.valid = false;
    return result;
}