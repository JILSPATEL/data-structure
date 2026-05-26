# A4_BellmanFordAlgorithm

## Overview
Bellman-Ford is an algorithm for finding shortest paths from a single source vertex to all other vertices in a weighted graph. It works even when edge weights are negative, as long as there is no negative weight cycle reachable from the source.

## When to use
- Graph has negative edge weights
- Need shortest distances from one source to every vertex
- Need to detect negative weight cycles

## Key idea
The algorithm repeatedly relaxes all edges. Relaxing an edge means checking whether the known distance to the destination vertex can be improved by going through the current edge.

After repeating relaxation `V - 1` times (where `V` is the number of vertices), all shortest distances are found if no negative cycle exists.

## Algorithm steps
1. Initialize a distance array `dist[]` with `infinity` for every vertex.
2. Set `dist[source] = 0`.
3. Repeat the following for `V - 1` times:
   - For each edge `(u, v, w)` in the graph:
     - If `dist[u] + w < dist[v]`, update `dist[v] = dist[u] + w`.
4. To detect a negative weight cycle, check all edges once more:
   - If any edge can still be relaxed, the graph contains a negative cycle.

## Pseudocode
```text
function BellmanFord(graph, source):
    dist = array of size |V| with all values = infinity
    dist[source] = 0

    for i from 1 to |V| - 1:
        for each edge (u, v, w) in graph:
            if dist[u] != infinity and dist[u] + w < dist[v]:
                dist[v] = dist[u] + w

    for each edge (u, v, w) in graph:
        if dist[u] != infinity and dist[u] + w < dist[v]:
            return "Graph contains a negative weight cycle"

    return dist
```

## Complexity
- Time: `O(V * E)`
- Space: `O(V + E)` for graph storage and `O(V)` for `dist[]`

## Example
Consider a graph with 5 vertices: `A, B, C, D, E`.

Edges:
- `A -> B (6)`
- `A -> C (7)`
- `B -> C (8)`
- `B -> D (5)`
- `B -> E (-4)`
- `C -> D (-3)`
- `C -> E (9)`
- `D -> B (-2)`
- `E -> D (7)`

### Initialization
- `dist[A] = 0`
- `dist[B] = ∞`
- `dist[C] = ∞`
- `dist[D] = ∞`
- `dist[E] = ∞`

### First iteration (relax all edges)
- Relax `A -> B`: `0 + 6 < ∞` → `dist[B] = 6`
- Relax `A -> C`: `0 + 7 < ∞` → `dist[C] = 7`
- Relax `B -> C`: `6 + 8 < 7`? No
- Relax `B -> D`: `6 + 5 < ∞` → `dist[D] = 11`
- Relax `B -> E`: `6 + (-4) < ∞` → `dist[E] = 2`
- Relax `C -> D`: `7 + (-3) < 11` → `dist[D] = 4`
- Relax `C -> E`: `7 + 9 < 2`? No
- Relax `D -> B`: `4 + (-2) < 6` → `dist[B] = 2`
- Relax `E -> D`: `2 + 7 < 4`? No

Distances now:
- `A = 0`
- `B = 2`
- `C = 7`
- `D = 4`
- `E = 2`

### Second iteration
- Relax `A -> B`: no change
- Relax `A -> C`: no change
- Relax `B -> C`: `2 + 8 < 7`? No
- Relax `B -> D`: `2 + 5 < 4`? No
- Relax `B -> E`: `2 + (-4) < 2` → `dist[E] = -2`
- Relax `C -> D`: no change
- Relax `C -> E`: no change
- Relax `D -> B`: no change
- Relax `E -> D`: `-2 + 7 < 4`? No

Distances now:
- `A = 0`
- `B = 2`
- `C = 7`
- `D = 4`
- `E = -2`

### Third iteration
- Only one update is possible again:
- Relax `B -> E`: `2 + (-4) < -2`? No
- All other relaxations do not reduce distances

### Fourth iteration
- No further updates occur

### Negative cycle check
- Check every edge one more time.
- Since no edge can be relaxed further, there is no negative cycle.

### Final shortest distances from `A`
- `A = 0`
- `B = 2`
- `C = 7`
- `D = 4`
- `E = -2`

## How to understand Bellman-Ford
- Start with the source distance as 0 and all others as infinity.
- Use edge relaxation to gradually improve the known distances.
- Repeat `V - 1` times because the longest simple path can have at most `V - 1` edges.
- If an edge can still improve a distance after `V - 1` passes, a negative cycle exists.

## Notes
- Bellman-Ford can handle negative edge weights.
- It is slower than Dijkstra for graphs without negative weights.
- It is a good choice when negative weights exist or when you need cycle detection.

## Example use cases
- Finding shortest paths in a graph with negative costs
- Detecting infeasible routes in currency exchange graphs
- Checking for negative cycles in transportation and scheduling systems
