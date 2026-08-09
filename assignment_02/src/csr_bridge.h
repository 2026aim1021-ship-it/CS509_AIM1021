#ifndef CSR_BRIDGE_H
#define CSR_BRIDGE_H

#include <vector>
using namespace std;

struct csr_graph{
    int V = 0;
    int E = 0;
    vector<int> row_ptr;
    vector<int> col_idx;
    vector<long long> values;
};

csr_graph buildCSR(int V,const vector<vector<pair<int,long long>>> &adj);

#endif