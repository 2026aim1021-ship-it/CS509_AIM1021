// Random graph generator for Assignment 2 (Bellman-Ford / Floyd-Warshall test data).
//
// Usage:
//   gen_graph bf <V> <E> <outfile> <source>
//   gen_graph fw <V> <outfile>
//
// Design notes (see assignment 4.1 / 4.2 / 5 / 6 for the required formats and sizes):
//   - Every edge only goes from a lower-indexed vertex to a higher-indexed vertex
//     (u < v). A graph built only from forward edges can never contain a cycle,
//     so it is guaranteed to have no negative-weight cycle even though individual
//     edge weights are allowed to be negative.
//   - For every vertex v > 0, one "backbone" edge is created from a random
//     u in [0, v-1] before any extra random edges are added. Because vertex 1's
//     only possible predecessor is 0, and every later vertex's predecessor is
//     itself already reachable from 0, source vertex 0 is guaranteed to reach
//     every vertex. Generated test files should therefore be run with source 0.
//   - Weights are drawn from [-10, 50] so both algorithms exercise negative
//     edges without ever producing a negative cycle.

#include <bits/stdc++.h>
using namespace std;

static void generateBellmanFord(long long V, long long E, const string &outfile, int source){
    mt19937_64 rng(12345);
    uniform_int_distribution<long long> weightDist(-10, 50);

    long long maxEdges = V * (V - 1) / 2;
    if (E > maxEdges) E = maxEdges;
    if (E < V - 1) E = V - 1;

    vector<vector<pair<int,long long>>> adj(V);

    // backbone: guarantees every vertex is reachable from vertex 0
    for (long long v = 1; v < V; v++){
        uniform_int_distribution<long long> pick(0, v - 1);
        long long u = pick(rng);
        adj[u].push_back({(int)v, weightDist(rng)});
    }

    long long extra = E - (V - 1);
    for (long long i = 0; i < extra; i++){
        uniform_int_distribution<long long> pickU(0, V - 2);
        long long u = pickU(rng);
        uniform_int_distribution<long long> pickV(u + 1, V - 1);
        long long v = pickV(rng);
        adj[u].push_back({(int)v, weightDist(rng)});
    }

    long long actualE = 0;
    for (long long u = 0; u < V; u++) actualE += (long long)adj[u].size();

    ofstream fout(outfile);
    if (!fout){
        cerr << "Error: cannot open " << outfile << " for writing\n";
        exit(1);
    }

    fout << V << " " << actualE << "\n";
    for (long long u = 0; u < V; u++){
        fout << u << " " << adj[u].size();
        for (auto &e : adj[u]){
            fout << " " << e.first << " " << e.second;
        }
        fout << "\n";
    }
    fout << "SOURCE " << source << "\n";

    cout << "Generated Bellman-Ford graph: V=" << V << " E=" << actualE
         << " source=" << source << " -> " << outfile << "\n";
}

static void generateFloydWarshall(long long V, const string &outfile){
    mt19937_64 rng(54321);
    uniform_int_distribution<long long> weightDist(-10, 50);
    const long long NOEDGE = LLONG_MIN;

    long long E = V * 3;
    long long maxEdges = V * (V - 1) / 2;
    if (E > maxEdges) E = maxEdges;
    if (E < V - 1) E = V - 1;

    vector<vector<long long>> mat(V, vector<long long>(V, NOEDGE));

    for (long long v = 1; v < V; v++){
        uniform_int_distribution<long long> pick(0, v - 1);
        long long u = pick(rng);
        if (mat[u][v] == NOEDGE) mat[u][v] = weightDist(rng);
    }

    long long extra = E - (V - 1);
    for (long long i = 0; i < extra; i++){
        uniform_int_distribution<long long> pickU(0, V - 2);
        long long u = pickU(rng);
        uniform_int_distribution<long long> pickV(u + 1, V - 1);
        long long v = pickV(rng);
        if (mat[u][v] == NOEDGE) mat[u][v] = weightDist(rng);
    }

    ofstream fout(outfile);
    if (!fout){
        cerr << "Error: cannot open " << outfile << " for writing\n";
        exit(1);
    }

    fout << V << "\n";
    for (long long i = 0; i < V; i++){
        for (long long j = 0; j < V; j++){
            if (j) fout << " ";
            if (i == j) fout << 0;
            else if (mat[i][j] == NOEDGE) fout << "INF";
            else fout << mat[i][j];
        }
        fout << "\n";
    }

    cout << "Generated Floyd-Warshall matrix: V=" << V << " -> " << outfile << "\n";
}

int main(int argc, char *argv[]){
    if (argc < 2){
        cerr << "Usage:\n  gen_graph bf <V> <E> <outfile> <source>\n  gen_graph fw <V> <outfile>\n";
        return 1;
    }

    string mode = argv[1];

    if (mode == "bf"){
        if (argc < 6){
            cerr << "Usage: gen_graph bf <V> <E> <outfile> <source>\n";
            return 1;
        }
        long long V = atoll(argv[2]);
        long long E = atoll(argv[3]);
        string outfile = argv[4];
        int source = atoi(argv[5]);
        generateBellmanFord(V, E, outfile, source);
    }
    else if (mode == "fw"){
        if (argc < 4){
            cerr << "Usage: gen_graph fw <V> <outfile>\n";
            return 1;
        }
        long long V = atoll(argv[2]);
        string outfile = argv[3];
        generateFloydWarshall(V, outfile);
    }
    else{
        cerr << "Unknown mode '" << mode << "', expected 'bf' or 'fw'\n";
        return 1;
    }

    return 0;
}
