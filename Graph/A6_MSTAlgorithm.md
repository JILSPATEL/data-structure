# A6_MSTAlgorithm

## Overview
Minimum Spanning Tree (MST) finds a spanning tree of an undirected weighted graph such that the sum of its edge weights is minimized.

A spanning tree includes all vertices and exactly `N - 1` edges for a graph with `N` nodes, and it has no cycles.

## When to use
- Graph is undirected and weighted
- Need to connect all nodes with minimum total weight
- Graph may have multiple MSTs but any one with minimum cost is acceptable

## Key idea
Kruskal’s Algorithm builds MST by selecting the smallest weight edges first, using a Disjoint Set Union (DSU) structure to avoid cycles.

## Algorithm steps
1. Sort all edges by increasing weight.
2. Initialize DSU for all vertices.
3. Iterate through sorted edges:
   - If the current edge connects two different components, add it to the MST.
   - Merge the two components in DSU.
4. Stop when the MST has `N - 1` edges.

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
        return -1 // graph not fully connected
    return mstWeight
```

## DSU operations
- `find(x)`: returns the leader of the component containing `x`.
- `unite(x, y)`: joins two components if they are different.
- Path compression and union by rank/size keep operations nearly constant time.

## Complexity
- Time: `O(E log E + E * α(N))`, where `α(N)` is the inverse Ackermann function.
- Space: `O(N)` for DSU arrays and `O(E)` for edges.

## Example
Given nodes `0..4` and edges:
- `(0, 1, 2)`
- `(0, 3, 6)`
- `(1, 2, 3)`
- `(1, 3, 8)`
- `(1, 4, 5)`
- `(2, 4, 7)`

Sorted by weight:
- `(0, 1, 2)`
- `(1, 2, 3)`
- `(1, 4, 5)`
- `(0, 3, 6)`
- `(2, 4, 7)`
- `(1, 3, 8)`

Select edges in order while avoiding cycles:
- Add `(0, 1, 2)` → connect 0 and 1
- Add `(1, 2, 3)` → connect 2
- Add `(1, 4, 5)` → connect 4
- Add `(0, 3, 6)` → connect 3

MST weight = `2 + 3 + 5 + 6 = 16`

## Notes
- Kruskal’s Algorithm is ideal for sparse graphs.
- If the graph is already sorted or edges are stored in a structure with efficient ordering, MST can be built quickly.
- If the graph is disconnected, no valid MST exists for all nodes.
