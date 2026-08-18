# Assignment 03 - Minimum Spanning Tree (Kruskal / Prim)

### Assignment Mode
Individual

### Objective
Given a weighted, undirected, connected graph, compute a Minimum Spanning Tree two different ways: Kruskal's algorithm (sort all edges, then add them greedily with union-find) and Prim's algorithm (grow one tree from vertex 0 using a min-priority queue). Both run on the same CSR graph and must report the same total MST weight, even if the specific edge sets differ. Only the algorithm call itself is timed.

### Algorithm / Approach
Reuses `buildCSR()` from `assignment_02/src/csr_bridge.h`/`.cpp` (not copied, called directly) to convert the adjacency list read from the input file into CSR (`row_ptr`, `col_idx`, `values`) before either algorithm starts - this conversion is preprocessing and isn't part of the timed region.

`kruskalMST()` extracts each undirected edge once from the CSR (only keeping `row u -> v` when `u < v`, since the input lists every edge in both adjacency lists with the same weight), sorts the edge list by weight, then adds edges greedily with a union-find (disjoint set union, with path compression) structure, skipping any edge whose endpoints are already connected. This extraction and sort happen inside the timed Kruskal call, per the assignment's timing rule.

`primMST()` grows a single tree from vertex 0 using a lazy-deletion min-priority queue: pop the cheapest frontier edge, skip it if the vertex is already included, otherwise add it to the tree and push its outgoing edges with their updated keys.

Both report `valid = false` if fewer than V-1 edges get selected, i.e. the input graph turned out to be disconnected, instead of printing a partial/incorrect tree.

`driver/main.cpp` takes `kruskal`, `prim`, or `mst` (runs both back to back, for direct comparison) as the first argument and the input file path as the second. It reads and validates the adjacency-list file, builds the CSR graph once, times only the algorithm call(s) with `std::chrono::high_resolution_clock`, and prints the MST edges, total weight, and execution time.

### Input Format
`mst_*.txt`: `V E` on the first line (E = number of undirected edges, each counted once even though it is listed in both adjacency lists), then V lines of `u degree n1 w1 n2 w2 ...`. Edge weights may be positive, zero, or negative.

### Test Data
`mst_example.txt` is the worked example straight from the assignment PDF (section 5.2), used as a known-answer sanity check - expected total weight 16, matching section 5.3 exactly.

`mst_10.txt`, `mst_100.txt`, `mst_10000.txt`, `mst_50000.txt`, `mst_100000.txt` were produced with `tools/gen_mst_graph.cpp`: a random spanning-tree backbone (vertex v connects to a random u < v) guarantees the graph is connected before extra random edges are added up to the target E, keeping the two largest graphs sparse (E is roughly 2V-4V, per the "keep large graphs sparse" note in section 4.2). Weights are drawn from [-10, 50] so both positive and negative/zero weights get exercised, since the assignment explicitly allows all three.

### File Structure
- `src/mst_common.h` - shared `mst_edge` / `mst_result` structs
- `src/kruskal.h`, `kruskal.cpp` - Kruskal's algorithm (edge extraction + sort + union-find)
- `src/prim.h`, `prim.cpp` - Prim's algorithm (min-priority queue over the CSR graph)
- `driver/main.cpp` - takes `<kruskal|prim|mst> <input file>`, builds CSR (via `assignment_02/src/csr_bridge.h`, not copied), times and runs the algorithm(s), prints the result
- `tools/gen_mst_graph.cpp` - random connected weighted graph generator, takes `<V> <E> <outfile>`
- `tests/` - input files
- `outputs/` - captured output for every test file

### Compilation
```
g++ -std=c++17 -O2 -o assignment_03/driver/main assignment_02/src/csr_bridge.cpp assignment_03/src/kruskal.cpp assignment_03/src/prim.cpp assignment_03/driver/main.cpp
```

### Execution
```
assignment_03/driver/main mst assignment_03/tests/mst_10.txt
```
`kruskal` or `prim` can be used instead of `mst` to time just one algorithm. Also runnable through the common wrapper (option 3: 1 to compile, 2 to compile the generator, 3 to generate test graphs, 4 to run all MST tests).

### Test Cases and Result Table

| Test File | V | E | Kruskal Wt. | Prim Wt. | Kruskal Time | Prim Time | Equal? | Expected Wt. | Status |
|---|---|---|---|---|---|---|---|---|---|
| mst_example.txt | 5 | 7 | 16 | 16 | 0.0022 ms | 0.0015 ms | Yes | 16 (PDF section 5.3) | Pass |
| mst_10.txt | 10 | 20 | 78 | 78 | 0.0030 ms | 0.0110 ms | Yes | - (generated graph) | Ran, no crash |
| mst_100.txt | 100 | 250 | 216 | 216 | 0.0214 ms | 0.0200 ms | Yes | - | Ran, no crash |
| mst_10000.txt | 10000 | 30000 | 14393 | 14393 | 2.3755 ms | 4.0764 ms | Yes | - | Ran, no crash |
| mst_50000.txt | 50000 | 150000 | 74800 | 74800 | 20.3528 ms | 43.0894 ms | Yes | - | Ran, no crash |
| mst_100000.txt | 100000 | 300000 | 148122 | 148122 | 35.6179 ms | 68.8937 ms | Yes | - | Ran, no crash |

No test at any size produced a core dump, crash, or a disconnected-graph failure. Kruskal and Prim agree on total MST weight on every test.

### Complexity
Kruskal: O(E log E) time, dominated by sorting the edge list (edge extraction is O(E), union-find with path compression is close to O(E * alpha(V))). O(V + E) memory for the CSR arrays plus the edge list and DSU parent array.

Prim: O(E log V) time with a binary min-heap (lazy-deletion priority queue). O(V + E) memory.

Both are within the same asymptotic class here; Prim is consistently slower than Kruskal in the measured times mainly because it re-pushes a heap entry every time a vertex's key improves rather than decreasing it in place, whereas Kruskal's cost is dominated by one `std::sort` over the extracted edge list.

### Known Limitations / To Do
- The DSU used by Kruskal has path compression but no union-by-rank/size. This is acceptable at the required sizes (the random-tree backbone used by the generator keeps `find()` chains shallow) but would be worth adding if graph sizes grow substantially beyond 100,000 vertices.
- Only vertex 0 is exercised as Prim's start vertex, per the assignment's reproducibility recommendation (section 2.1.2); `primMST()` accepts any start vertex via its second argument.
