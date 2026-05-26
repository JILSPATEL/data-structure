# A5_FloydWarshallAlgorithm

## Overview
Floyd-Warshall is an algorithm that finds the shortest paths between every pair of vertices in a weighted graph. It works for directed or undirected graphs and can handle negative edge weights, as long as there are no negative weight cycles.

## When to use
- Need shortest distance between every pair of vertices
- Graph can have negative edge weights
- Graph size is small to medium, because the algorithm is `O(V^3)`

## Key idea
The algorithm uses dynamic programming. It builds shortest paths step-by-step by allowing intermediate vertices.

At each step, we decide whether a path from `i` to `j` should go through a vertex `k` or not.

## Algorithm steps
1. Create a 2D distance matrix `dist[][]` of size `V x V`.
2. Initialize `dist[i][j]` with the weight of edge `(i, j)` if it exists, otherwise use `infinity`.
3. Set `dist[i][i] = 0` for every vertex `i`.
4. For each vertex `k` from `0` to `V-1`:
   - For each vertex `i` from `0` to `V-1`:
     - For each vertex `j` from `0` to `V-1`:
       - If `dist[i][k]` and `dist[k][j]` are not infinity and `dist[i][k] + dist[k][j] < dist[i][j]`, then update:
         - `dist[i][j] = dist[i][k] + dist[k][j]`

## Pseudocode
```text
function FloydWarshall(graph):
    dist = matrix of size |V| x |V|

    for i from 0 to |V|-1:
        for j from 0 to |V|-1:
            if i == j:
                dist[i][j] = 0
            else if edge (i, j) exists:
                dist[i][j] = weight(i, j)
            else:
                dist[i][j] = infinity

    for k from 0 to |V|-1:
        for i from 0 to |V|-1:
            for j from 0 to |V|-1:
                if dist[i][k] != infinity and dist[k][j] != infinity and dist[i][k] + dist[k][j] < dist[i][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]

    return dist
```

## Complexity
- Time: `O(V^3)`
- Space: `O(V^2)`

## Example
Consider a graph with 4 vertices: `A, B, C, D`.

Edges:
- `A -> B (3)`
- `A -> C (8)`
- `A -> D (-4)`
- `B -> D (7)`
- `B -> C (1)`
- `C -> B (4)`
- `D -> A (2)`
- `D -> C (6)`

### Step 1: Initialize matrix
Let `∞` represent infinity.

Initial distance matrix:

|   | A | B | C | D |
|---|---|---|---|---|
| A | 0 | 3 | 8 | -4 |
| B | ∞ | 0 | 1 | 7  |
| C | ∞ | 4 | 0 | ∞  |
| D | 2 | ∞ | 6 | 0  |

### Step 2: Add intermediate vertices one by one
We will use each vertex as a possible intermediate stop.

#### Using `A` as intermediate (`k = A`)
- Check if any path `i -> A -> j` is shorter than `i -> j`.
- No distance improves for this example.

#### Using `B` as intermediate (`k = B`)
- Update `A -> C`: `A -> B + B -> C = 3 + 1 = 4`, which is less than `8`.
- Update `D -> C`: `D -> A + A -> B + B -> C` is not needed because direct `D -> C = 6` is already shorter.

Matrix after `B`:

|   | A | B | C | D |
|---|---|---|---|---|
| A | 0 | 3 | 4 | -4 |
| B | ∞ | 0 | 1 | 7  |
| C | ∞ | 4 | 0 | ∞  |
| D | 2 | ∞ | 6 | 0  |

#### Using `C` as intermediate (`k = C`)
- Update `B -> A`: no path through `C` shorter than `∞`.
- Update `D -> B`: `D -> C + C -> B = 6 + 4 = 10`, which is less than `∞`.

Matrix after `C`:

|   | A | B | C | D |
|---|---|---|---|---|
| A | 0 | 3 | 4 | -4 |
| B | ∞ | 0 | 1 | 7  |
| C | ∞ | 4 | 0 | ∞  |
| D | 2 | 10| 6 | 0  |

#### Using `D` as intermediate (`k = D`)
- Update `B -> A`: `B -> D + D -> A = 7 + 2 = 9`
- Update `C -> A`: `C -> B + B -> D + D -> A` is longer than `∞`, but with direct updates from earlier, we keep best values.

Matrix after `D`:

|   | A | B | C | D |
|---|---|---|---|---|
| A | 0 | 3 | 4 | -4 |
| B | 9 | 0 | 1 | 7  |
| C | 13| 4 | 0 | 11 |
| D | 2 | 10| 6 | 0  |

### Final answer
The final `dist[][]` matrix gives shortest distances between every pair:
- Shortest distance from `A` to `C` is `4`.
- Shortest distance from `B` to `A` is `9`.
- Shortest distance from `D` to `B` is `10`.

## How to understand Floyd-Warshall
- Start with direct distances between vertices.
- Allow paths to use one extra intermediate vertex at each step.
- After allowing all possible intermediate vertices, the matrix contains shortest distances for every pair.

## Notes
- Useful for all-pairs shortest paths, not just single-source.
- Handles negative edge weights, but not negative cycles.
- If `dist[i][i]` becomes negative, the graph has a negative cycle.

## Example use cases
- Computing all-pairs travel times in a small network
- Finding shortest delivery routes between every city pair
- Solving problems where every node needs distance to every other node
