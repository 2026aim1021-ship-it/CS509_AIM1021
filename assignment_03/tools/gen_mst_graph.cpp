// Random weighted, connected, undirected graph generator for Assignment 3
// MST test data (Kruskal / Prim).
//
// Usage:
//   gen_mst_graph <V> <E> <outfile>
//
// Design notes (see assignment sections 4.2 and 5 for required sizes/format):
//   - A random spanning-tree backbone (vertex v connects to a random u < v)
//     is added first, guaranteeing the graph is connected before any extra
//     edges are added - required since MST inputs must be connected.
//   - Extra random edges (no duplicates, no self loops) are added until E is
//     reached, keeping large graphs sparse (E around 2V-4V, per the
//     assignment's recommendation).
//   - Weights are drawn from [-10, 50] since MST edge weights may be
//     positive, zero or negative.
//   - Every edge is written into BOTH endpoints' adjacency lists with the
//     same weight, as required by the undirected MST input format.

#include <bits/stdc++.h>
using namespace std;

int main(int argc,char *argv[]){
    if(argc<4){
        cerr << "Usage: gen_mst_graph <V> <E> <outfile>\n";
        return 1;
    }

    long long V = atoll(argv[1]);
    long long E = atoll(argv[2]);
    string outfile = argv[3];

    if(V<=0){
        cerr << "Error: V must be positive\n";
        return 1;
    }

    long long maxEdges = V*(V-1)/2;
    if(E>maxEdges) E=maxEdges;
    if(E<V-1) E=V-1;

    mt19937_64 rng(20260815);
    uniform_int_distribution<long long> weightDist(-10,50);

    vector<vector<pair<int,long long>>> adj(V);
    set<pair<int,int>> used;

    auto addEdge=[&](long long u,long long v,long long w){
        if(u>v) swap(u,v);
        used.insert({(int)u,(int)v});
        adj[u].push_back({(int)v,w});
        adj[v].push_back({(int)u,w});
    };

    // backbone: guarantees connectivity (every vertex reachable from 0)
    for(long long v=1;v<V;v++){
        uniform_int_distribution<long long> pick(0,v-1);
        long long u=pick(rng);
        addEdge(u,v,weightDist(rng));
    }

    long long attempts=0;
    long long maxAttempts=E*20+1000;

    while((long long)used.size()<E && attempts<maxAttempts){
        attempts++;
        uniform_int_distribution<long long> pickA(0,V-1);
        long long a=pickA(rng);
        long long b=pickA(rng);
        if(a==b) continue;
        long long uu=min(a,b), vv=max(a,b);
        if(used.count({(int)uu,(int)vv})) continue;
        addEdge(uu,vv,weightDist(rng));
    }

    long long actualE = (long long)used.size();

    ofstream fout(outfile);
    if(!fout){
        cerr << "Error: cannot open " << outfile << " for writing\n";
        return 1;
    }

    fout << V << " " << actualE << "\n";
    for(long long u=0;u<V;u++){
        fout << u << " " << adj[u].size();
        for(auto &e:adj[u]){
            fout << " " << e.first << " " << e.second;
        }
        fout << "\n";
    }

    cout << "Generated MST graph: V=" << V << " E=" << actualE << " -> " << outfile << "\n";
    return 0;
}
