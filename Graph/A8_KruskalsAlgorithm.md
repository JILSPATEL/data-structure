# A8_KruskalsAlgorithm

## Overview
Kruskal’s Algorithm finds the Minimum Spanning Tree (MST) of an undirected weighted graph by selecting edges in ascending order of weight and adding each edge if it does not create a cycle.

## When to use
- Graph is undirected and weighted
- Need a minimum-cost spanning tree
- Graph may be sparse or edges can be easily sorted

## Key idea
Sort all edges by weight, then iterate through them. Add each edge to the MST only if it connects two previously disconnected components. Use a Disjoint Set Union (DSU) structure to detect cycles efficiently.

## Algorithm steps
1. Sort all edges by weight in non-decreasing order.
2. Initialize a DSU for all vertices.
3. Initialize `mstWeight = 0` and `edgesUsed = 0`.
4. For each edge `(u, v, w)` in sorted order:
   - If `u` and `v` are in different DSU components:
     - Unite them in DSU.
     - Add `w` to `mstWeight`.
     - Increment `edgesUsed`.
   - Stop when `edgesUsed == n - 1`.
5. If the graph is connected, return `mstWeight`; otherwise return `-1`.

## Pseudocode
```text
function KruskalMST(n, edges):
    sort edges by weight ascending
    dsu = new DSU(n)
    mstWeight = 0
    edgesUsed = 0

    for each edge (u, v, w) in edges:
        if dsu.find(u) != dsu.find(v):
            dsu.unite(u, v)
            mstWeight += w
            edgesUsed += 1
            if edgesUsed == n - 1:
                break

    if edgesUsed != n - 1:
        return -1 // graph is disconnected
    return mstWeight
```

## DSU operations
- `find(x)`: returns the representative parent of node `x`.
- `unite(x, y)`: merges the two components containing `x` and `y`.
- Use path compression and union by rank/size for nearly constant amortized time.

## Complexity
- Time: `O(E log E + E * α(N))` where `α(N)` is the inverse Ackermann function.
- Space: `O(N + E)`.

## Example
Given `N = 5` vertices `0, 1, 2, 3, 4` and edges:
- `(0, 1, 2)`
- `(0, 3, 6)`
- `(1, 2, 3)`
- `(1, 3, 8)`
- `(1, 4, 5)`
- `(2, 4, 7)`

### Step-by-step execution
#### Step 1: Sort edges by weight
1. `(0, 1, 2)`
2. `(1, 2, 3)`
3. `(1, 4, 5)`
4. `(0, 3, 6)`
5. `(2, 4, 7)`
6. `(1, 3, 8)`

#### Step 2: Process sorted edges
- Edge `(0, 1, 2)`:
  - `0` and `1` are in different components.
  - Add edge to MST.
  - `mstWeight = 2`, `edgesUsed = 1`.

- Edge `(1, 2, 3)`:
  - `1` and `2` are different.
  - Add edge to MST.
  - `mstWeight = 5`, `edgesUsed = 2`.

- Edge `(1, 4, 5)`:
  - `1` and `4` are different.
  - Add edge to MST.
  - `mstWeight = 10`, `edgesUsed = 3`.

- Edge `(0, 3, 6)`:
  - `0` and `3` are different.
  - Add edge to MST.
  - `mstWeight = 16`, `edgesUsed = 4`.

- At this point, `edgesUsed == n - 1`, so the algorithm stops.

#### Step 3: Final MST
Selected edges:
- `(0, 1, 2)`
- `(1, 2, 3)`
- `(1, 4, 5)`
- `(0, 3, 6)`

### Final weight
- `2 + 3 + 5 + 6 = 16`

## Notes
- Kruskal’s Algorithm is especially effective when edges are fewer than `V^2`.
- It can build an MST for disconnected graphs only for each connected component, but not a single full MST.
- When multiple edges have equal weight, any valid edge ordering among them still produces an MST.
