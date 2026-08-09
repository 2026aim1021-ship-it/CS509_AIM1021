#ifndef FLLOYD_WARSHALL
#define FLLOYD_WARSHALL

#include <vector>
#include <string>
using namespace std;

#ifndef GRAPH_INF_DEFINED
#define GRAPH_INF_DEFINED
const long long INF = (long long)4e18;
#endif

struct denseMatrix{
    int V = 0;
    vector<vector<long long>> dist;
};

denseMatrix readMatrix(const string &path);

struct floydWarshallResult{
    vector<vector<long long>> dist;
    bool cycle = false;
};

floydWarshallResult floydWarshall(const denseMatrix &matrix);

#endif