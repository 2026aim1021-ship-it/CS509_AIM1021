#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

#include "../src/bellmanFord.h"
#include "../src/flloydWarshall.h"
#include "../src/csr_bridge.h"

using namespace std;
using namespace std::chrono;

bool runBellmanFord(const string &path){
    ifstream fp(path);
    if(!fp){
        cerr<<"Error : Input file not opening : "<< path << "\n";
        return false;
    }

    int V,E;
    fp >> V >> E;

    vector<vector<pair<int, long long>>> adj(V);

    for(int i=0;i<V;i++){
        int u,degree;
        fp>>u>>degree;
        for(int j=0;j<degree;j++){
            int v;
            long long wt;
            fp>>v>>wt;
            adj[u].push_back({v,wt});
        }
    }

    string tag;
    int source;

    fp>>tag>>source;

    if (tag!="SOURCE"){
        cout<<"Error: expected SOURCE \n";
        return false;
    }

    csr_graph g = buildCSR(V,adj);
    auto start = high_resolution_clock::now();
    bellmanFord_res result = bellmanFord(&g,source);
    auto end = high_resolution_clock::now();

    double ms = duration<double, milli>(end-start).count();

    cout<<"Algorithm Bellman Ford : \n";

    if (result.negativeCyc){
        cout << "Negative Cycle : true\n";
        return false;
    }
    else{
        cout << "Vertex distance : ";
        for(int i=0;i<V;i++){
            cout << i << " " << result.distances[i] << "\n";
        }

        cout << "Exec time " << ms << "ms \n";
        return true;
    }
}

bool runFlloydWarshall(const string &path){
    denseMatrix m = readMatrix(path);
    if (m.V==0){
        cerr<<"Error:cannot open or parse input file";
        return false;
    }

    auto start = high_resolution_clock::now();
    floydWarshallResult result = floydWarshall(m);
    auto end = high_resolution_clock::now();

    double ms = duration<double,milli>(end-start).count();
    cout<<"Algorithm Flloyd Warshall : \n";
    if(result.cycle){
        cout<<"Negative cycle:true\n";
        return false;
    }else{
        cout<<"Distance matrix : \n";
        for(int i=0;i<m.V;i++){
            for(int j=0;j<m.V;j++){
                cout << result.dist[i][j] << " ";
            }
            cout << "\n";
        }
        cout<<"Negative cycle : None";
    }
    cout<<"Execution time : " << ms << "ms \n";
    return true;
}

int main(int argc,char *argv[]){
    if (argc<3){
        cerr << "Less arguements";
        return 1;
    }

    string algorithm = argv[1];
    string path = argv[2];

    if (algorithm=="bf"){
        return runBellmanFord(path)?0:1;
    }

    if(algorithm=="fw"){
        return runFlloydWarshall(path)?0:1;
    }

    cerr << "Error : Unknown algorithm \n";
    return 1;
}