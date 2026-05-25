# A3_DijkstraAlgorithm

## Overview
Dijkstra's Algorithm finds the shortest path from a single source vertex to all other vertices in a weighted graph with non-negative edge weights.

## When to use
- Weighted directed or undirected graphs
- Edge weights are non-negative
- Need shortest distances from one source to all reachable nodes

## Key idea
Start from the source, then repeatedly select the currently unvisited vertex with the smallest known distance. Update its neighbors’ distances using the selected vertex. Continue until all reachable vertices are processed.

## Algorithm steps
1. Initialize a distance array `dist[]` with `infinity` for every vertex.
2. Set `dist[source] = 0`.
3. Create a min-priority queue (min-heap) with `(distance, vertex)` pairs.
4. While the queue is not empty:
   - Extract the vertex `u` with the smallest `dist[u]`.
   - If the extracted distance is greater than the stored `dist[u]`, skip it.
   - For each neighbor `v` of `u` with edge weight `w`:
     - If `dist[u] + w < dist[v]`, update `dist[v] = dist[u] + w` and push `(dist[v], v)` into the queue.
5. After processing, `dist[]` contains the shortest distances from the source.

## Pseudocode
```text
function Dijkstra(graph, source):
    dist = array of size |V| with all values = infinity
    dist[source] = 0
    minHeap = empty min-priority queue
    push (0, source) into minHeap

    while minHeap is not empty:
        (d, u) = extract-min(minHeap)
        if d > dist[u]:
            continue
        for each edge (u, v, w) in graph:
            if dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                push (dist[v], v) into minHeap

    return dist
```

## Complexity
- Time: `O((V + E) log V)` with a binary heap
- Space: `O(V + E)` for graph storage and `O(V)` for `dist[]`

## Example
Consider this weighted graph:

Vertices: `A, B, C, D, E`

Edges:
- `A -> B (2)`
- `A -> C (4)`
- `B -> C (1)`
- `B -> D (7)`
- `C -> E (3)`
- `D -> E (1)`

### Step-by-step execution from source `A`

Initial distances:
- `dist[A] = 0`
- `dist[B] = ∞`
- `dist[C] = ∞`
- `dist[D] = ∞`
- `dist[E] = ∞`

Priority queue initially: `(0, A)`

1. Extract `(0, A)`
   - Relax `A -> B`: `0 + 2 < ∞` → `dist[B] = 2`
   - Relax `A -> C`: `0 + 4 < ∞` → `dist[C] = 4`
   - Push `(2, B)`, `(4, C)`

Distances now: A=0, B=2, C=4, D=∞, E=∞
Queue: `(2, B), (4, C)`

2. Extract `(2, B)`
   - Relax `B -> C`: `2 + 1 < 4` → `dist[C] = 3`
   - Relax `B -> D`: `2 + 7 < ∞` → `dist[D] = 9`
   - Push `(3, C)`, `(9, D)`

Distances now: A=0, B=2, C=3, D=9, E=∞
Queue: `(3, C), (4, C), (9, D)`

3. Extract `(3, C)`
   - Relax `C -> E`: `3 + 3 < ∞` → `dist[E] = 6`
   - Push `(6, E)`

Distances now: A=0, B=2, C=3, D=9, E=6
Queue: `(4, C), (9, D), (6, E)`

4. Extract `(4, C)`
   - This entry is stale because `4 > dist[C]` (3), so skip.

Queue: `(6, E), (9, D)`

5. Extract `(6, E)`
   - `E` has no outgoing edges in this example.

Queue: `(9, D)`

6. Extract `(9, D)`
   - Relax `D -> E`: `9 + 1 = 10`, but `10 >= dist[E] (6)`, so no update.

Queue is empty. Algorithm ends.

### Final shortest distances from `A`
- `A = 0`
- `B = 2`
- `C = 3`
- `D = 9`
- `E = 6`

## Notes
- Dijkstra's Algorithm is not correct for negative edge weights.
- Using a min-heap ensures efficient selection of the smallest tentative distance.
- In a dense graph, using a Fibonacci heap can reduce complexity to `O(E + V log V)`.

## Variations
- Track predecessors to reconstruct shortest paths
- Use adjacency list representation for efficiency
- Use priority queue with decrease-key or lazy insertion for updates
