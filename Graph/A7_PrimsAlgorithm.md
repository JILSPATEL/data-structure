# A7_PrimsAlgorithm

## Overview
Prim’s Algorithm finds the Minimum Spanning Tree (MST) of an undirected weighted graph by growing the tree from a starting node and repeatedly adding the least-weight edge that connects a vertex in the tree to a vertex outside it.

## When to use
- Graph is undirected and weighted
- Need a minimum-cost tree connecting all vertices
- Graph may be dense, since Prim’s with a min-heap works well

## Key idea
Start from any vertex and maintain a set of vertices included in the MST. At each step, choose the smallest weight edge that connects the MST set to a vertex not yet in the MST.

## Algorithm steps
1. Choose any arbitrary starting vertex and mark it as part of the MST.
2. Create a min-priority queue of edges that cross from the MST set to the non-MST vertices.
3. While the MST set has fewer than `N` vertices:
   - Extract the minimum-weight edge `(u, v)` from the queue.
   - If `v` is already in the MST set, skip it.
   - Otherwise, add `v` to the MST, and include the edge weight in the total MST cost.
   - Add all edges from `v` to vertices not yet in the MST into the priority queue.
4. Repeat until all vertices are included or no crossing edge remains.

## Pseudocode
```text
function PrimMST(n, graph, start = 0):
    visited = array of size n with all values = false
    minHeap = empty min-priority queue of (weight, u, v)
    totalWeight = 0
    visited[start] = true

    for each edge (start, v, w) in graph:
        push (w, start, v) into minHeap

    while minHeap is not empty and number of visited vertices < n:
        (w, u, v) = extract-min(minHeap)
        if visited[v]:
            continue
        visited[v] = true
        totalWeight += w
        for each edge (v, x, w2) in graph:
            if not visited[x]:
                push (w2, v, x) into minHeap

    if all vertices visited:
        return totalWeight
    return -1 // graph disconnected
```

## Complexity
- Time: `O((V + E) log E)` with a binary heap, which is `O(E log E)` or `O(E log V)`
- Space: `O(E + V)` for storing the graph and heap edges

## Example
Consider the following graph with 5 vertices `0, 1, 2, 3, 4` and edges:
- `(0, 1, 2)`
- `(0, 3, 6)`
- `(1, 2, 3)`
- `(1, 3, 8)`
- `(1, 4, 5)`
- `(2, 4, 7)`

### Step-by-step execution
Start at vertex `0`.

#### Step 1: Initialize
- MST vertices: `{0}`
- Candidate edges: `(0, 1, 2)`, `(0, 3, 6)`
- Total MST weight: `0`

#### Step 2: Pick smallest edge
- Choose `(0, 1, 2)`
- Add vertex `1` to MST
- Total weight: `2`
- New candidates from `1`: `(1, 2, 3)`, `(1, 3, 8)`, `(1, 4, 5)`
- Candidates now: `(0, 3, 6)`, `(1, 2, 3)`, `(1, 3, 8)`, `(1, 4, 5)`

#### Step 3: Pick smallest edge
- Choose `(1, 2, 3)`
- Add vertex `2` to MST
- Total weight: `5`
- New candidates from `2`: `(2, 4, 7)`
- Candidates now: `(0, 3, 6)`, `(1, 4, 5)`, `(1, 3, 8)`, `(2, 4, 7)`

#### Step 4: Pick smallest edge
- Choose `(1, 4, 5)`
- Add vertex `4` to MST
- Total weight: `10`
- Vertex `4` offers no smaller crossing edges than existing candidates
- Candidates now: `(0, 3, 6)`, `(2, 4, 7)`, `(1, 3, 8)`

#### Step 5: Pick smallest edge
- Choose `(0, 3, 6)`
- Add vertex `3` to MST
- Total weight: `16`
- All vertices are now included in the MST.

### Final MST edges
- `(0, 1, 2)`
- `(1, 2, 3)`
- `(1, 4, 5)`
- `(0, 3, 6)`

### Total weight
- `2 + 3 + 5 + 6 = 16`

## Notes
- Prim’s Algorithm can start from any vertex; the MST cost remains the same for connected graphs.
- It is especially efficient on dense graphs when using adjacency matrix or optimized priority queues.
- If the graph is disconnected, the algorithm will not be able to visit all vertices and no MST exists for the full graph.
