# Assignment 02 - Shortest Paths (Bellman-Ford / Floyd-Warshall)

### Assignment Mode
Individual

### Objective
Given a graph as input, compute shortest paths two different ways: Bellman-Ford (single source, handles negative edge weights, directed graph, CSR input) and Floyd-Warshall (all pairs, dense matrix input). Both report a negative-weight cycle instead of a distance if one is found, and both are timed on the algorithm call only.

### Algorithm / Approach
`csr_bridge.h/.cpp` holds `buildCSR()`, which turns an adjacency list (built while reading the input file) into the three CSR arrays (`row_ptr`, `col_idx`, `values`). This conversion happens before the timer starts, since it's preprocessing and not part of the algorithm.

`bellmanFord()` relaxes every edge in the CSR graph V-1 times, stopping early if a full pass makes no changes. A final extra pass checks whether any edge can still be relaxed - if so, a negative cycle is reachable from the source and the distance table is skipped.

`readMatrix()` reads the dense V x V matrix directly (Floyd-Warshall doesn't go through CSR, per the assignment). `floydWarshall()` runs the standard triple loop over every intermediate vertex k, then checks the diagonal of the result - a negative diagonal entry means a negative cycle exists.

`driver/main.cpp` takes `bf` or `fw` as the first argument and the input file path as the second, times only the algorithm call with `std::chrono::high_resolution_clock`, and prints the result.

### Input Format
Bellman-Ford (`bf_*.txt`): `V E` on the first line, then V lines of `u degree n1 w1 n2 w2 ...`, then `SOURCE s`.

Floyd-Warshall (`fw_*.txt`): `V` on the first line, then V rows of V space-separated integers or the token `INF`.

### Test Data
`bf_1.txt` and `fw_1.txt` are the worked examples straight from the assignment PDF (sections 5.2 and 6.2), used as a known-answer sanity check.

`bf_10.txt`, `bf_100.txt`, `bf_10000.txt`, `bf_50000.txt`, `bf_100000.txt` and `fw_10.txt`, `fw_100.txt`, `fw_500.txt`, `fw_1000.txt`, `fw_2000.txt` were produced with a small generator: every edge only goes from a lower-indexed vertex to a higher one, so the graph is a DAG and can't contain a cycle at all - this guarantees no negative-weight cycle even with random negative weights (drawn from [-10, 50]). Every vertex is wired so it's reachable from vertex 0, so all Bellman-Ford runs use source 0. Bellman-Ford edge counts are kept around 3V, in line with the "keep the two largest graphs sparse" note in section 4.2.

### File Structure
- `src/csr_bridge.h`, `csr_bridge.cpp` - adjacency list to CSR conversion
- `src/bellmanFord.h`, `bellmanFord.cpp` - Bellman-Ford over the CSR graph
- `src/flloydWarshall.h`, `flloydWarshall.cpp` - dense matrix reader + Floyd-Warshall
- `driver/main.cpp` - takes `<bf|fw> <input file>`, times and runs the algorithm, prints the result
- `tests/` - input files
- `outputs/` - captured output for every test file

### Compilation
```
g++ -std=c++17 -O2 -o assignment_02/driver/main assignment_02/src/csr_bridge.cpp assignment_02/src/bellmanFord.cpp assignment_02/src/flloydWarshall.cpp assignment_02/driver/main.cpp
```

### Execution
```
assignment_02/driver/main bf assignment_02/tests/bf_10.txt
assignment_02/driver/main fw assignment_02/tests/fw_10.txt
```
Also runnable through the common wrapper (option 2: compile, run Bellman-Ford tests, run Floyd-Warshall tests).

### Test Cases and Result Table

**Bellman-Ford**

| Test File | Vertices | Edges | Source | Negative Cycle | Expected Output | Actual Output | Time | Status |
|---|---|---|---|---|---|---|---|---|
| bf_1.txt | 5 | 10 | 0 | No | Distances 0,2,4,7,-2 (PDF section 5.3) | Matches | 0.0008 ms | Pass |
| bf_10.txt | 10 | 30 | 0 | No | - (generated graph, no hand-computed answer) | see outputs/bf_10_out.txt | 0.0018 ms | Ran, no crash |
| bf_100.txt | 100 | 300 | 0 | No | - | see outputs/bf_100_out.txt | 0.0093 ms | Ran, no crash |
| bf_10000.txt | 10000 | 30000 | 0 | No | - | see outputs/bf_10000_out.txt | 0.6846 ms | Ran, no crash |
| bf_50000.txt | 50000 | 150000 | 0 | No | - | see outputs/bf_50000_out.txt | 3.5034 ms | Ran, no crash |
| bf_100000.txt | 100000 | 300000 | 0 | No | - | see outputs/bf_100000_out.txt | 5.9127 ms | Ran, no crash |

**Floyd-Warshall**

| Test File | Vertices | Negative Cycle | Expected Output | Actual Output | Time | Status |
|---|---|---|---|---|---|---|
| fw_1.txt | 5 | No | Distance matrix (PDF section 6.3) | Matches | 0.0037 ms | Pass |
| fw_10.txt | 10 | No | - | see outputs/fw_10_out.txt | 0.0059 ms | Ran, no crash |
| fw_100.txt | 100 | No | - | see outputs/fw_100_out.txt | 0.9037 ms | Ran, no crash |
| fw_500.txt | 500 | No | - | see outputs/fw_500_out.txt | 10.0146 ms | Ran, no crash |
| fw_1000.txt | 1000 | No | - | see outputs/fw_1000_out.txt | 45.9782 ms | Ran, no crash |
| fw_2000.txt | 2000 | No | - | see outputs/fw_2000_out.txt (~75 MB) | 316.024 ms | Ran, no crash |

No test at any size produced a core dump or failed to complete.

### Complexity
Bellman-Ford: O(V*E) time, O(V+E) memory for the CSR arrays plus O(V) for the distance array.

Floyd-Warshall: O(V^3) time, O(V^2) memory for the distance matrix - this is why it's capped at 2000 vertices instead of the 50,000/100,000 scale used elsewhere.

### Known Limitations / To Do
- Section 6.3 asks that, for the sizes required by both algorithms (10 and 100 vertices), Bellman-Ford be run from every vertex as source and cross-checked against the matching row of the Floyd-Warshall output for the *same* graph. 


