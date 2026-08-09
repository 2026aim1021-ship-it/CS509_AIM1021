#include "flloydWarshall.h"

#include <iostream>
#include <fstream>

denseMatrix readMatrix(const string &path){
    denseMatrix m;
    ifstream fp(path);

    if(!fp){
        cerr<<"Error: can't open "<<path<<"\n";
        return m;
    }

    fp >> m.V;

    m.dist.assign(m.V,vector<long long>(m.V,0));

    for(int i=0;i<m.V;i++){
        for(int j=0;j<m.V;j++){
            string tok;
            fp >> tok;
            m.dist[i][j] = (tok=="INF")? INF : atoll(tok.c_str());
        }
    }

    return m;
}


floydWarshallResult floydWarshall(const denseMatrix &matrix){
    floydWarshallResult res;
    int V = matrix.V;
    res.dist = matrix.dist;

    for(int k=0;k<V;k++){
        for(int i=0;i<V;i++){
            if (res.dist[i][k]>=INF)
                continue;
            for(int j=0;j<V;j++){
                if (res.dist[k][j] >=INF)
                    continue;

                if (res.dist[i][k]+res.dist[k][j]<res.dist[i][j]){
                    res.dist[i][j] = res.dist[i][k] + res.dist[k][j];
                }                
            }
        }
    }

    for(int i=0;i<V;i++){
        if (res.dist[i][i]<0){
            res.cycle = true;
            break;
        }
    }

    return res;
}