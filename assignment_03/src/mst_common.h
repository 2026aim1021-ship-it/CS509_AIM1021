#ifndef MST_COMMON_H
#define MST_COMMON_H

#include <bits/stdc++.h>
using namespace std;

struct mst_edge{
    int u;
    int v;
    long long w;
};

struct mst_result{
    vector<mst_edge> edges;
    long long totalWeight = 0;
    bool valid = true;
};

#endif

