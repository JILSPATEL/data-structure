# Kahn's Algorithm (Topological Sorting using BFS)

## Introduction

Topological Sorting is a technique used in a **Directed Acyclic Graph (DAG)** to arrange nodes in such a way that:

> For every directed edge `u → v`,
> node `u` appears before node `v`.

Kahn’s Algorithm is a **BFS-based approach** used for:

* Topological Sorting
* Detecting Cycle in Directed Graph

---

# Why Kahn’s Algorithm Works

The main idea is:

* A node having **indegree = 0**
  means no node depends on it.
* So we can safely process it first.

After removing that node:

* Reduce indegree of its neighbors.
* Any neighbor whose indegree becomes `0`
  can now be processed.

---

# Important Terms

## 1. Directed Graph

A graph where edges have direction.

Example:

```text
0 → 1 → 2
```

---

## 2. Indegree

Indegree of a node =
Number of incoming edges.

Example:

```text
0 → 1 ← 2
```

Indegree of `1` = 2

---

# Kahn’s Algorithm Steps

## Step 1: Create Adjacency List

Store all outgoing edges.

---

## Step 2: Find Indegree of Every Node

Count incoming edges for each node.

---

## Step 3: Push All Nodes with Indegree 0 into Queue

These nodes can appear first in topological order.

---

## Step 4: Perform BFS

While queue is not empty:

* Remove node
* Add to answer
* Reduce indegree of neighbors
* If neighbor indegree becomes 0:
  push into queue

---

## Step 5: Check Number of Visited Nodes

### If:

```text
visited == V
```

→ No cycle exists

### Else:

```text
visited != V
```

→ Cycle exists

Because some nodes never became indegree 0.

---

# Dry Run Example (No Cycle)

## Graph

```text
0 → 1 → 2 → 3
```

---

## Initial Indegree

| Node | Indegree |
| ---- | -------- |
| 0    | 0        |
| 1    | 1        |
| 2    | 1        |
| 3    | 1        |

---

## Queue Initially

```text
[0]
```

---

## Processing

### Remove 0

```text
Visited = 1
```

Reduce indegree of 1:

```text
1 becomes 0
```

Push 1.

Queue:

```text
[1]
```

---

### Remove 1

```text
Visited = 2
```

Reduce indegree of 2:

```text
2 becomes 0
```

Queue:

```text
[2]
```

---

### Remove 2

```text
Visited = 3
```

Reduce indegree of 3:

```text
3 becomes 0
```

Queue:

```text
[3]
```

---

### Remove 3

```text
Visited = 4
```

Queue becomes empty.

---

## Final Condition

```text
visited = 4
V = 4
```

So:

```text
visited == V
```

✅ No cycle exists.

---

# Dry Run Example (Cycle Exists)

## Graph

```text
0 → 1 → 2 → 3
     ↑       ↓
     └───────┘
```

Cycle:

```text
1 → 2 → 3 → 1
```

---

## Indegree

| Node | Indegree |
| ---- | -------- |
| 0    | 0        |
| 1    | 2        |
| 2    | 1        |
| 3    | 1        |

---

## Queue Initially

```text
[0]
```

---

## Remove 0

Visited = 1

Reduce indegree of 1:

```text
2 → 1
```

Still not zero.

Queue becomes empty.

---

## Final Condition

```text
visited = 1
V = 4
```

So:

```text
visited != V
```

✅ Cycle exists.

---

# Visual Intuition

Think of nodes as tasks.

A task can only be done when all prerequisites are completed.

* Indegree = number of prerequisites
* Indegree 0 = ready to execute

Kahn’s Algorithm repeatedly executes ready tasks.

If some tasks never become ready,
a cycle exists.

---

# Time Complexity

## Building Graph

```text
O(E)
```

---

## Calculating Indegree

```text
O(E)
```

---

## BFS Traversal

```text
O(V + E)
```

---

# Total Complexity

```text
O(V + E)
```

---

# Space Complexity

```text
O(V + E)
```

Because of:

* adjacency list
* queue
* indegree array

---

# Full VS Code Format Code

```cpp
/**
 * Kahn's Algorithm
 * Detect Cycle in Directed Graph using BFS
 *
 * Time Complexity: O(V + E)
 * Space Complexity: O(V + E)
 */

class Solution {
public:

    bool isCyclic(int V, vector<vector<int>>& edges) {

        // Step 1: Create adjacency list
        vector<vector<int>> adj(V);

        for (auto &it : edges) {
            adj[it[0]].push_back(it[1]);
        }

        // Step 2: Calculate indegree
        vector<int> inDeg(V, 0);

        for (int i = 0; i < V; i++) {
            for (auto &it : adj[i]) {
                inDeg[it]++;
            }
        }

        // Step 3: Push nodes with indegree 0
        queue<int> q;

        for (int i = 0; i < V; i++) {
            if (inDeg[i] == 0) {
                q.push(i);
            }
        }

        // Step 4: BFS Traversal
        int visited = 0;

        while (!q.empty()) {

            int node = q.front();
            q.pop();

            visited++;

            for (auto &it : adj[node]) {

                inDeg[it]--;

                if (inDeg[it] == 0) {
                    q.push(it);
                }
            }
        }

        // Step 5: Cycle Detection
        return visited != V;
    }
};
```

---

# When to Use Kahn’s Algorithm

Use when:

✅ Topological Sorting required
✅ Detect cycle in directed graph
✅ Dependency ordering problems
✅ Course Schedule problems
✅ Build systems / task scheduling

---

# Important Interview Point

## Kahn’s Algorithm ONLY works for:

✅ Directed Graph

---

## For Undirected Graph Cycle Detection

Use:

* BFS with parent tracking
* DFS with parent tracking
* DSU (Union Find)

---

# Key Observation

## DAG Always Has At Least One Node with Indegree 0

But in a cycle:

```text
Every node depends on another node
```

So no node gets indegree 0 eventually.
