# Disjoint Set Union (DSU) --- Union and Find Concept (Detailed Explanation)

## 1. What is DSU?

Disjoint Set Union (DSU), also called **Union Find**, is a data
structure used to manage a collection of non-overlapping sets.

It mainly supports two operations:

1.  **Find**
    -   Find which set a particular element belongs to.
    -   Returns the representative (leader/parent) of that set.
2.  **Union**
    -   Merge two different sets into one set.

DSU is commonly used in: - Detecting cycles in graphs - Kruskal's
Minimum Spanning Tree algorithm - Finding connected components - Dynamic
connectivity problems

------------------------------------------------------------------------

# 2. Basic Idea

Suppose we have elements:

    1 2 3 4 5

Initially, every element is its own separate set:

    1    2    3    4    5

Each element is its own parent:

    parent[1] = 1
    parent[2] = 2
    parent[3] = 3
    parent[4] = 4
    parent[5] = 5

The parent represents the leader of that group.

------------------------------------------------------------------------

# 3. Find Operation

## Purpose

The `find()` operation finds the ultimate parent (root) of a node.

Example:

          1
         /
        2
       /
      3

Parent array:

    parent[1] = 1
    parent[2] = 1
    parent[3] = 2

Finding parent of 3:

    find(3)

    3 -> parent is 2
    2 -> parent is 1
    1 -> parent is 1

    Answer = 1

So node 3 belongs to the set whose leader is 1.

------------------------------------------------------------------------

# 4. Simple Find Code

``` cpp
int find(int node)
{
    if(parent[node] == node)
        return node;

    return find(parent[node]);
}
```

Problem:

For a long chain:

    1 <- 2 <- 3 <- 4 <- 5

Finding 5 takes O(N) time.

To optimize this, we use **Path Compression**.

------------------------------------------------------------------------

# 5. Path Compression Optimization

## Concept

While finding the ultimate parent, directly attach every visited node to
the root.

Before:

    1
    |
    2
    |
    3
    |
    4
    |
    5

Calling:

    find(5)

After path compression:

        1
     / / \ \
    2 3 4 5

Now future searches become faster.

------------------------------------------------------------------------

# 6. Find With Path Compression

``` cpp
int find(int node)
{
    if(parent[node] == node)
        return node;

    return parent[node] = find(parent[node]);
}
```

This line:

``` cpp
parent[node] = find(parent[node]);
```

updates the parent directly to the ultimate parent.

------------------------------------------------------------------------

# 7. Union Operation

## Purpose

Union joins two different sets.

Example:

Before:

    Set A:

    1
    |
    2


    Set B:

    3
    |
    4

Operation:

    union(2,4)

First find leaders:

    find(2)=1
    find(4)=3

Now connect leaders:

    3 -> 1

Result:

        1
       / \
      2   3
          |
          4

------------------------------------------------------------------------

# 8. Simple Union Code

``` cpp
void unionSet(int u,int v)
{
    int pu=find(u);
    int pv=find(v);

    if(pu!=pv)
    {
        parent[pv]=pu;
    }
}
```

Problem:

The tree can become very tall.

To solve this: - Union by Rank - Union by Size

------------------------------------------------------------------------

# 9. Union By Rank

## What is Rank?

Rank roughly represents the height of a tree.

Initially:

    rank[i]=0

When merging:

-   Smaller rank tree goes under bigger rank tree.
-   If both ranks are equal, choose one as parent and increase its rank.

Example:

Before:

    rank[1]=2

          1
         / \
        2   3


    rank[4]=1

          4
         /
        5

Since rank of 1 is bigger:

Attach 4 below 1:

            1
          / | \
         2  3  4
               |
               5

------------------------------------------------------------------------

# 10. Union By Rank Code

``` cpp
void unionRank(int u,int v)
{
    int pu=find(u);
    int pv=find(v);

    if(pu==pv)
        return;

    if(rank[pu] < rank[pv])
    {
        parent[pu]=pv;
    }
    else if(rank[pv] < rank[pu])
    {
        parent[pv]=pu;
    }
    else
    {
        parent[pv]=pu;
        rank[pu]++;
    }
}
```

------------------------------------------------------------------------

# 11. Union By Size

## Concept

Maintain size of every component.

Smaller component attaches to larger component.

Initially:

    size[i]=1

because every node is alone.

Example:

    Component A size = 5

    Component B size = 2

Attach B into A.

------------------------------------------------------------------------

# 12. Union By Size Code

``` cpp
void unionSize(int u,int v)
{
    int pu=find(u);
    int pv=find(v);

    if(pu==pv)
        return;


    if(size[pu] < size[pv])
    {
        parent[pu]=pv;
        size[pv]+=size[pu];
    }
    else
    {
        parent[pv]=pu;
        size[pu]+=size[pv];
    }
}
```

------------------------------------------------------------------------

# 13. Complete DSU Class C++

``` cpp
class DSU {
public:

    vector<int> parent;
    vector<int> size;

    DSU(int n)
    {
        parent.resize(n);
        size.resize(n,1);

        for(int i=0;i<n;i++)
            parent[i]=i;
    }


    int find(int node)
    {
        if(parent[node]==node)
            return node;

        return parent[node]=find(parent[node]);
    }


    void unionSet(int u,int v)
    {
        int pu=find(u);
        int pv=find(v);


        if(pu==pv)
            return;


        if(size[pu]<size[pv])
        {
            parent[pu]=pv;
            size[pv]+=size[pu];
        }
        else
        {
            parent[pv]=pu;
            size[pu]+=size[pv];
        }
    }
};
```

------------------------------------------------------------------------

# 14. Time Complexity

With:

-   Path Compression
-   Union by Rank / Size

Complexity:

    Find  -> O(α(N))
    Union -> O(α(N))

α(N) = Inverse Ackermann Function

For practical values:

    α(N) <= 5

So DSU operations are almost O(1).

------------------------------------------------------------------------

# 15. Summary

  Operation          Purpose
  ------------------ ---------------------------------------
  Find               Find ultimate parent/component leader
  Union              Merge two components
  Path Compression   Makes find faster
  Union by Rank      Keeps tree height small
  Union by Size      Keeps smaller tree below larger tree

DSU = Efficient way to handle dynamic connected components.
