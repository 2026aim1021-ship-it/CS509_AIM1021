#ifndef BELLMAN_FORD
#define BELLMAN_FORD

#include "csr_bridge.h"
#include <vector>
using namespace std;

#ifndef GRAPH_INF_DEFINED
#define GRAPH_INF_DEFINED
const long long INF = (long long)4e18;
#endif

struct bellmanFord_res{
    vector<long long> distances;
    bool negativeCyc = false;
};

bellmanFord_res bellmanFord(const csr_graph *graph,int source);

#endif