
# DFS and BFS Complete Notes

---


# 1. Introduction

Graphs are one of the most important data structures in programming.

Many real-world systems can be represented using graphs:

- Social Networks
- Google Maps
- Computer Networks
- Flight Routes
- Web Pages
- Recommendation Systems

To process graphs efficiently, we use traversal algorithms.

The two most important traversal algorithms are:

1. DFS (Depth First Search)
2. BFS (Breadth First Search)

---

# 2. What is a Graph?

A graph is a collection of:

- Vertices (Nodes)
- Edges (Connections)

Example:

```text
    A ----- B
    |       |
    |       |
    C ----- D
```

Vertices:
A, B, C, D

Edges:
(A-B), (A-C), (B-D), (C-D)

---

# 3. Types of Graphs

## 1. Undirected Graph

Edges work both directions.

```text
A ---- B
```

Meaning:
A ↔ B

---

## 2. Directed Graph

Edges have direction.

```text
A ---> B
```

Meaning:
A can go to B only.

---

## 3. Weighted Graph

Edges contain weights/cost.

```text
A --5--> B
```

---

# 4. Graph Representation

---

## Adjacency Matrix

Example:

```text
    0 1 1 0
    1 0 0 1
    1 0 0 1
    0 1 1 0
```

Space Complexity:
O(V²)

---

## Adjacency List

Most commonly used.

```text
0 -> 1, 2
1 -> 0, 3
2 -> 0, 3
3 -> 1, 2
```

Space Complexity:
O(V + E)

---

# 5. What is Traversal?

Traversal means visiting all nodes of a graph.

Two main ways:

1. DFS → Go deep first
2. BFS → Visit level by level

---

# 6. Depth First Search (DFS)

DFS explores as deep as possible before backtracking.

Think of it like:

* Exploring a maze
* Going into one tunnel fully
* Then coming back

DFS uses:

* Recursion
  OR
* Stack

---

# Example Graph

```text
            0
          /   \
         1     2
        / \   / \
       3   4 5   6
```

Adjacency List:

```text
0 -> 1, 2
1 -> 0, 3, 4
2 -> 0, 5, 6
3 -> 1
4 -> 1
5 -> 2
6 -> 2
```

---

# 7. DFS Traversal Visualization

Start Node = 0

Traversal Order:

```text
0 → 1 → 3 → BACKTRACK → 4 → BACKTRACK → 0 → 2 → 5 → BACKTRACK → 6
```

Final DFS Traversal:

```text
0 1 3 4 2 5 6
```

---

# DFS Step-by-Step

## Step 1

Visit 0

Visited:

```text
0
```

---

## Step 2

Go to 1

Visited:

```text
0 1
```

---

## Step 3

Go to 3

Visited:

```text
0 1 3
```

3 has no unvisited neighbor.

BACKTRACK

---

## Step 4

Go to 4

Visited:

```text
0 1 3 4
```

BACKTRACK

---

## Step 5

Back to 0

Go to 2

Visited:

```text
0 1 3 4 2
```

---

## Step 6

Go to 5

Visited:

```text
0 1 3 4 2 5
```

BACKTRACK

---

## Step 7

Go to 6

Visited:

```text
0 1 3 4 2 5 6
```

DFS Complete.

---

# 8. DFS Recursive Tree

```text
                    dfs(0)
                   /      \
             dfs(1)      dfs(2)
             /    \       /   \
        dfs(3) dfs(4) dfs(5) dfs(6)
```

This recursive structure is called:

RECURSION TREE

---

# Important DFS Concept

DFS always:

1. Goes deep
2. Finishes one path
3. Then backtracks

---

# 9. DFS Code (C++)

```cpp
/**
 * DFS Traversal using Recursion
 *
 * Time Complexity : O(V + E)
 * Space Complexity: O(V)
 */

class Solution {
public:

    void dfs(int node,
             vector<vector<int>>& adj,
             vector<int>& vis,
             vector<int>& ans) {

        vis[node] = 1;

        ans.push_back(node);

        for (auto &neighbor : adj[node]) {

            if (!vis[neighbor]) {

                dfs(neighbor, adj, vis, ans);
            }
        }
    }

    vector<int> dfsOfGraph(int V,
                           vector<vector<int>>& adj) {

        vector<int> vis(V, 0);

        vector<int> ans;

        dfs(0, adj, vis, ans);

        return ans;
    }
};
```

---

# 10. DFS Complexity

## Time Complexity

```text
O(V + E)
```

Where:

* V = Vertices
* E = Edges

---

## Space Complexity

```text
O(V)
```

Because of:

* Visited array
* Recursion stack

---

# 11. Breadth First Search (BFS)

BFS explores level by level.

Think like:

* Ripple in water
* Fire spreading equally

BFS uses:

QUEUE

(FIFO)

---

# Same Example Graph

```text
            0
          /   \
         1     2
        / \   / \
       3   4 5   6
```

---

# 12. BFS Traversal Visualization

Start Node = 0

Level-wise traversal:

```text
Level 0:
0

Level 1:
1 2

Level 2:
3 4 5 6
```

Final BFS Traversal:

```text
0 1 2 3 4 5 6
```

---

# 13. BFS Queue Visualization

---

## Step 1

Queue:

```text
[0]
```

Pop 0

Push neighbors:
1, 2

Queue:

```text
[1, 2]
```

Traversal:

```text
0
```

---

## Step 2

Pop 1

Push:
3, 4

Queue:

```text
[2, 3, 4]
```

Traversal:

```text
0 1
```

---

## Step 3

Pop 2

Push:
5, 6

Queue:

```text
[3, 4, 5, 6]
```

Traversal:

```text
0 1 2
```

---

## Step 4

Pop 3

Queue:

```text
[4, 5, 6]
```

Traversal:

```text
0 1 2 3
```

---

## Step 5

Pop 4

Queue:

```text
[5, 6]
```

Traversal:

```text
0 1 2 3 4
```

---

## Step 6

Pop 5

Queue:

```text
[6]
```

Traversal:

```text
0 1 2 3 4 5
```

---

## Step 7

Pop 6

Queue:

```text
[]
```

Traversal:

```text
0 1 2 3 4 5 6
```

BFS Complete.

---

# BFS Tree Structure

```text
                    0
                 /     \
                1       2
              /  \    /   \
             3    4  5     6
```

BFS traverses level by level.

---

# 14. BFS Code (C++)

```cpp
/**
 * BFS Traversal
 *
 * Time Complexity : O(V + E)
 * Space Complexity: O(V)
 */

class Solution {
public:

    vector<int> bfsOfGraph(int V,
                           vector<vector<int>>& adj) {

        vector<int> vis(V, 0);

        vector<int> ans;

        queue<int> q;

        q.push(0);

        vis[0] = 1;

        while (!q.empty()) {

            int node = q.front();

            q.pop();

            ans.push_back(node);

            for (auto &neighbor : adj[node]) {

                if (!vis[neighbor]) {

                    vis[neighbor] = 1;

                    q.push(neighbor);
                }
            }
        }

        return ans;
    }
};
```

---

# 15. BFS Complexity

## Time Complexity

```text
O(V + E)
```

---

## Space Complexity

```text
O(V)
```

Because queue may store all vertices.

---

# 16. DFS vs BFS

| Feature         | DFS                               | BFS                     |
| --------------- | --------------------------------- | ----------------------- |
| Data Structure  | Stack / Recursion                 | Queue                   |
| Traversal Style | Deep First                        | Level Wise              |
| Shortest Path   | Not Guaranteed                    | Guaranteed (Unweighted) |
| Memory Usage    | Less                              | More                    |
| Backtracking    | Yes                               | No                      |
| Used In         | Cycle Detection, Topological Sort | Shortest Path           |

---

# 17. When to Use DFS?

Use DFS when:

* Need recursion
* Need backtracking
* Need connected components
* Need cycle detection
* Need topological sort
* Need all possible paths

Examples:

* Sudoku Solver
* Maze Problems
* Tree Traversals

---

# 18. When to Use BFS?

Use BFS when:

* Need shortest path
* Need minimum steps
* Need level order traversal
* Need nearest node

Examples:

* Rotten Oranges
* Word Ladder
* Binary Tree Level Order
* Shortest Path in Unweighted Graph

---

# 19. Common Problems

## DFS Problems

* Number of Islands
* Cycle Detection
* Flood Fill
* Topological Sort
* Connected Components

---

## BFS Problems

* Rotten Oranges
* Word Ladder
* Minimum Steps
* 0-1 Matrix
* Number of Enclaves

---

# 20. Important Notes

## DFS can be implemented using:

1. Recursion
2. Explicit Stack

---

## BFS always uses Queue

FIFO Order:

```text
First In First Out
```

---

## Visited Array is Important

Without visited array:

* Infinite loops may happen
* Nodes may repeat

---

# Final Summary

## DFS

* Go deep first
* Uses recursion/stack
* Backtracks

Traversal Style:

```text
0 → 1 → 3 → BACKTRACK → 4
```

---

## BFS

* Visit level by level
* Uses queue
* Best for shortest path

Traversal Style:

```text
0 → 1 → 2 → 3 → 4 → 5 → 6
```

---

# End

```
```
