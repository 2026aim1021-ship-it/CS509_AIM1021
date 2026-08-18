#include <bits/stdc++.h>
#include "../src/prim.h"
#include "../src/kruskal.h"
#include "../../assignment_02/src/csr_bridge.h"

using namespace std;
using namespace chrono;

bool readMSTFile(const string &path,int &V,int &E,vector<vector<pair<int,long long>>> &adj){
    ifstream file(path);
    if(!file){
        cerr << "Error Cannot open file \n";
        return false;
    }

    file >> V >> E;
    if(!file || V<=0){
        cerr << "Error : Invalid V\n";
        return false;
    }

    adj.assign(V,{});

    for(int i=0;i<V;i++){
        int u,degree;

        file >> u >> degree;

        if (!file || u<0 || u>=V || degree<0){
            cerr << "Invalid arguements \n";
            return false;
        }

        for(int j=0;j<degree;j++){
            int v;
            long long w;

            file >> v >> w;
            if(!file || v<0 || v>=V){
                cerr << "Invalid arguements \n";
                return false;
            }

            adj[u].push_back({v,w});
        }
    }

    if(V>1){
        for(int u=0;u<V;u++){
            if(adj[u].empty()){
                cerr << "Error: isolated vertex " << u << " (graph with V>1 must be connected)\n";
                return false;
            }
        }
    }

    return true;
}

void printResult(string name,const mst_result &result,double time){
    cout << "Algorithm : " << name << "\n";
    if(!result.valid){
        cout << "Graph is not connected\n";
        cout << "Execution time : " << time << " ms\n";
        return;
    }

    cout << "MST edges:\n";
    for(auto e:result.edges)
        cout << e.u << " " << e.v << " " << e.w << "\n";

    cout << "Total MST weight: " << result.totalWeight << "\n";
    cout << "Execution time : " << time << " ms\n";

    return;
}

int main(int argc,char *argv[]){
    if (argc<3){
        cout << "Number of arguements not valid\n";
        return 1;
    }

    string algorithm = argv[1];
    string filename = argv[2];

    int V,E;
    vector<vector<pair<int,long long>>> adj;

    if(!readMSTFile(filename,V,E,adj))
        return 1;

    csr_graph graph = buildCSR(V,adj);

    if(algorithm == "kruskal"){
        auto start = high_resolution_clock::now();
        mst_result result = kruskalMST(&graph);
        auto end = high_resolution_clock::now();
        double time = duration<double,milli>(end-start).count();
        printResult("Kruskal's MST",result,time);
        return result.valid?0:1;
    }

    if(algorithm == "prim"){
        auto start = high_resolution_clock::now();
        mst_result result = primMST(&graph,0);
        auto end = high_resolution_clock::now();
        double time = duration<double,milli>(end-start).count();
        printResult("Prim's MST",result,time);
        return result.valid?0:1;
    }

    if(algorithm=="mst"){
        auto start1 = high_resolution_clock::now();
        mst_result kResult = kruskalMST(&graph);
        auto end1 = high_resolution_clock::now();
        double kTime = duration<double,milli>(end1-start1).count();

        auto start2 = high_resolution_clock::now();
        mst_result pResult = primMST(&graph,0);
        auto end2 = high_resolution_clock::now();
        double pTime = duration<double,milli>(end2-start2).count();

        printResult("Kruskal's MST", kResult, kTime);
        printResult("Prim's MST", pResult, pTime);

        if (kResult.valid && pResult.valid) {
            cout << "Equal total weight: "
                 << (kResult.totalWeight == pResult.totalWeight ? "Yes" : "No")
                 << "\n";
        }

        return (kResult.valid && pResult.valid) ? 0 : 1;
    }

    cerr << "Unknown algorithm\n";
    return 1;
}
