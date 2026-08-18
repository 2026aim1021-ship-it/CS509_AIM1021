#ifndef PRIM_H
#define PRIM_H

#include "mst_common.h"
#include "../../assignment_02/src/csr_bridge.h"

mst_result primMST(const csr_graph *graph,int startIndex=0);

#endif