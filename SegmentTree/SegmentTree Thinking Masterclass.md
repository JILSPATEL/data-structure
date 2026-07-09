# Segment Trees — A Complete Masterclass

This is not a list of code templates to memorize. It's a method for *deriving* and *building* the solution to any query-range/update-range problem from first principles. Every section follows a unified conceptual lens:

1. **How to recognize Segment Tree applies**
2. **How to choose what the node represents (State/Merge)**
3. **Why that representation (and not another)**
4. **How to derive the Merge operator**
5. **How to handle Query logic (No, Partial, Complete overlap)**
6. **How to handle Updates (Point vs Range)**
7. **How to write the recursion (Base cases, Midpoint, Children)**
8. **Memory layout (1-based vs 0-based, why 4N)**
9. **Lazy Propagation (when and why)**
10. **The general pattern this problem represents**

---

## PART 0 — The Recognition Lens

A problem is solvable (and optimal) with a Segment Tree when:

- **Range Queries exist.** You need to query an aggregate value (Sum, Min, Max, GCD, Prefix, etc.) over an arbitrary subarray range `[L, R]`.
- **Updates exist.** The underlying array is *mutable* — values can change at specific indices (Point Update) or across contiguous subsegments (Range Update).
- **Both operations are interleaved.** If the array is static (no updates), a simple **Prefix Sum Array** (for Sum) or **Sparse Table** (for Min/Max/GCD) provides \(O(1)\) queries after \(O(n \log n)\) preprocessing, which is strictly superior. Use a Segment Tree *only* when updates are mixed with queries.
- **Non-invertible operations are queried.** For simple range sums with point updates, a **Fenwick Tree (Binary Indexed Tree)** is shorter, faster, and uses \(O(n)\) space. However, Fenwick trees struggle with non-invertible operations like Range Max/Min or Range GCD. When the merge operation cannot be undone (i.e., has no inverse), Segment Tree is the standard solution.

---

## PART 1 — Foundations: Range Sum Query (Mutable)

> Given an array, support point updates at index `idx` and range sum queries over `[L, R]`.

**1. Recognition.** We have range queries (Sum) and point updates. The array is mutable. Both must run in \(O(\log n)\).

**2/3. State.** What does a node represent? Let `st[node]` store the sum of elements in the range `[l, r]` represented by that node. Why this state? Because range sum satisfies **associativity** and **combinability**: the sum of `[l, r]` is exactly the sum of `[l, mid]` plus the sum of `[mid+1, r]`.

**4. Merge Operator.** 
```
st[node] = st[left_child] + st[right_child]
```
The merge operator is addition (`+`). The identity element (what we return when a range is completely outside our query) is `0`, since `x + 0 = x`.

**5. Query Logic.** To query a range `[ql, qr]`, we traverse from the root. For the current node representing `[l, r]`:
- **No overlap**: `[ql, qr]` is completely outside `[l, r]`. Return the identity `0`.
- **Complete overlap**: `[l, r]` is a subset of `[ql, qr]`. Return `st[node]`.
- **Partial overlap**: Recurse on both children and merge: `query(left) + query(right)`.

**6. Updates.** Point update at `idx` with `val`. Locate the leaf representing index `idx` (where `l == r == idx`), update it, and re-merge all parent nodes on the way back up the recursion stack.

**7. Recursion.** 
- Base case: `l == r` -> `st[node] = arr[l]`.
- Midpoint: `mid = l + (r - l) / 2`.
- Left child: `build(2 * node, l, mid)`.
- Right child: `build(2 * node + 1, mid + 1, r)`.

**8. Memory Layout.** Stored in a flat 1D array of size `4n`. Using 1-based indexing: root is at `1`, left child is `2 * node`, right child is `2 * node + 1`.

---

## PART 2 — Query Logic: The Three Cases of Overlap

The core of Segment Tree query efficiency is how we resolve overlap. At any node representing range `[l, r]` when querying `[ql, qr]`:

```
               [  l  . . . . . . . . . .  r  ]  (Current Node Range)
               
Case 1:  [ql . . qr]                                                 (No Overlap)
Case 2:           [ql . . . . . . . . qr]                            (Complete Overlap)
Case 3:        [ql . . . . . . qr]                                   (Partial Overlap)
```

```cpp
int query(int node, int l, int r, int ql, int qr) {
    // Case 1: No overlap (Disjoint)
    if (ql > r || qr < l) {
        return 0; // Return identity element
    }
    
    // Case 2: Complete overlap (Subset)
    if (ql <= l && r <= qr) {
        return st[node];
    }
    
    // Case 3: Partial overlap (Intersect)
    int mid = l + (r - l) / 2;
    int left_query = query(2 * node, l, mid, ql, qr);
    int right_query = query(2 * node + 1, mid + 1, r, ql, qr);
    
    return left_query + right_query; // Merge step
}
```

---

## PART 3 — Updates: Point vs. Range

### Point Updates
A point update modifies a single element `arr[idx] = val`. This changes exactly one leaf node. Since the tree has height \(\lceil \log_2 n \rceil\), only \(O(\log n)\) ancestor nodes are affected. We recursively find the leaf, update it, and re-evaluate the ancestors.

```cpp
void updatePoint(int node, int l, int r, int idx, int val) {
    if (l == r) {
        st[node] = val; // Found leaf
        return;
    }
    int mid = l + (r - l) / 2;
    if (idx <= mid) {
        updatePoint(2 * node, l, mid, idx, val);
    } else {
        updatePoint(2 * node + 1, mid + 1, r, idx, val);
    }
    // Re-merge ancestors on the way up
    st[node] = st[2 * node] + st[2 * node + 1];
}
```

### The Range Update Bottleneck
If we want to update a range `[L, R]` (e.g., add `val` to all elements from `L` to `R`) using point updates, we must run `updatePoint` \(k\) times, where \(k = R - L + 1\). This results in a worst-case time complexity of \(O(n \log n)\), which is too slow. 

To achieve \(O(\log n)\) range updates, we need **Lazy Propagation**.

---

## PART 4 — Lazy Propagation: Range Updates in \(O(\log n)\)

The philosophy of Lazy Propagation is **deferral**: 
> *Never update children until you absolutely must visit them.*

If a range update completely covers a node's interval `[l, r]`, we update that node immediately and write the update to a `lazy` array for that node. We do **not** recurse into its children. When we later visit those children during a subsequent query or update, we "push" the pending lazy value down to them.

### The Three Steps at Every Node Visit
Whenever a function (query or update) visits a node `[l, r]`:
1. **Resolve Pending Updates**: If `lazy[node] != 0`, apply it to `st[node]` and propagate the value to `lazy[2*node]` and `lazy[2*node+1]`. Clear `lazy[node]`.
2. **Check Overlap**: Identify if we have No Overlap, Complete Overlap, or Partial Overlap.
3. **Execute/Split**:
   - On Complete Overlap: Apply the update immediately, update the lazy tags of children, and return.
   - On Partial Overlap: Recurse on children, then re-merge.

```cpp
// For Range Sum Query with Range Addition Updates
void updateRange(int node, int l, int r, int ul, int ur, int val) {
    // 1. Resolve pending updates
    if (lazy[node] != 0) {
        st[node] += (r - l + 1) * lazy[node]; // Apply addition to sum
        if (l != r) { // Not a leaf
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    // Out of bounds (No overlap)
    if (ul > r || ur < l) return;

    // Complete overlap
    if (ul <= l && r <= ur) {
        st[node] += (r - l + 1) * val;
        if (l != r) {
            lazy[2 * node] += val;
            lazy[2 * node + 1] += val;
        }
        return;
    }

    // Partial overlap
    int mid = l + (r - l) / 2;
    updateRange(2 * node, l, mid, ul, ur, val);
    updateRange(2 * node + 1, mid + 1, r, ul, ur, val);
    st[node] = st[2 * node] + st[2 * node + 1];
}
```

---

## PART 5 — Code Design & Architecture

Here is a clean, production-ready implementation of a **Range Sum Segment Tree with Lazy Propagation** (Range Addition Updates):

```cpp
#include <vector>
#include <iostream>

class LazySegmentTree {
private:
    int n;
    std::vector<long long> st;
    std::vector<long long> lazy;

    void push(int node, int l, int r) {
        if (lazy[node] == 0) return;
        
        // Apply update to current node
        st[node] += (r - l + 1) * lazy[node];
        
        // Propagate lazy tag to children
        if (l != r) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        
        // Clear current node lazy tag
        lazy[node] = 0;
    }

    void build(int node, int l, int r, const std::vector<int>& arr) {
        if (l == r) {
            st[node] = arr[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build(2 * node, l, mid, arr);
        build(2 * node + 1, mid + 1, r, arr);
        st[node] = st[2 * node] + st[2 * node + 1];
    }

    void update(int node, int l, int r, int ul, int ur, long long val) {
        push(node, l, r);
        if (ul > r || ur < l) return; // No overlap

        if (ul <= l && r <= ur) { // Complete overlap
            lazy[node] += val;
            push(node, l, r);
            return;
        }

        int mid = l + (r - l) / 2;
        update(2 * node, l, mid, ul, ur, val);
        update(2 * node + 1, mid + 1, r, ul, ur, val);
        st[node] = st[2 * node] + st[2 * node + 1];
    }

    long long query(int node, int l, int r, int ql, int qr) {
        push(node, l, r);
        if (ql > r || qr < l) return 0; // Identity element for Sum
        if (ql <= l && r <= qr) return st[node];

        int mid = l + (r - l) / 2;
        return query(2 * node, l, mid, ql, qr) + query(2 * node + 1, mid + 1, r, ql, qr);
    }

public:
    LazySegmentTree(const std::vector<int>& arr) {
        n = arr.size();
        st.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
        build(1, 0, n - 1, arr);
    }

    void updateRange(int L, int R, long long val) {
        update(1, 0, n - 1, L, R, val);
    }

    long long queryRange(int L, int R) {
        return query(1, 0, n - 1, L, R);
    }
};
```

---

## PART 6 — Space Complexity: Why \(4n\)?

Why do we allocate \(4n\) space when a binary tree of size \(n\) has only \(2n - 1\) nodes?

1. **Perfect Binary Tree Case**: If \(n\) is a power of 2 (e.g., \(n = 8\)), the tree is perfectly balanced. The leaf nodes are at depth \(k\), and the total number of nodes is:
   $$2^0 + 2^1 + 2^2 + \dots + 2^k = 2^{k+1} - 1 = 2n - 1$$
   Here, exactly \(2n\) size is sufficient.
2. **Worst Case (Skewed Leaf Placement)**: If \(n\) is not a power of 2 (e.g., \(n = 2^k + 1\)), the leaf nodes spill over to depth \(k+1\). In the flat array layout, child mapping is done strictly via `2 * node` and `2 * node + 1`. This leaves empty indices in the array.
   - For example, if \(n = 5\), the next power of 2 is \(8\).
   - The leaf nodes are placed at indices that map up to \(2 \times 7 + 1 = 15\) in the tree array.
   - Since \(15 < 4 \times 5\), the allocation of \(4n\) elements prevents out-of-bounds errors.
   - Mathematically, the maximum index reached in a flat binary tree array of size \(n\) is bounded by \(4n - 5\), which is less than \(4n\).

---

## PART 7 — Advanced Patterns & Variations

### 1. Range Minimum / Maximum Query (RMQ)
Used in problems requiring boundary queries (like [LFG_LLG.cpp](file:///d:/data-structure/SegmentTree/LFG_LLG.cpp)).
- **State**: `st[node]` stores the minimum or maximum in range `[l, r]`.
- **Merge**: `st[node] = std::max(st[2 * node], st[2 * node + 1])`.
- **Identity**: Return `INT_MIN` for Max queries, or `INT_MAX` for Min queries.

### 2. Segment Tree with Custom Node Structs
When you need to track multiple attributes simultaneously (e.g., maximum subarray sum, longest contiguous subsegment of a character).
- **State**: Define a custom `Node` struct containing multiple attributes.
- **Merge**: Write a custom merge function combining left and right sub-nodes:
```cpp
struct Node {
    int max_sum;
    int prefix_sum;
    int suffix_sum;
    int total_sum;
};

Node merge(Node left, Node right) {
    Node parent;
    parent.total_sum = left.total_sum + right.total_sum;
    parent.prefix_sum = std::max(left.prefix_sum, left.total_sum + right.prefix_sum);
    parent.suffix_sum = std::max(right.suffix_sum, right.total_sum + left.suffix_sum);
    parent.max_sum = std::max({left.max_sum, right.max_sum, left.suffix_sum + right.prefix_sum});
    return parent;
}
```

---

## PART 8 — The General Framework (apply this to ANY new Segment Tree problem)

When solving range query problems, use this checklist:

1. **Confirm Mutability**: Are there updates mixed with range queries? If no updates, use a Prefix Sum or Sparse Table.
2. **Check Operands**: Can this operation be computed by combining two adjacent segments? (e.g., Sum, Min, Max, GCD, Matrix Multiplication can. Median cannot).
3. **Define Node State**: Does a single variable suffice, or do you need a custom structure (e.g. prefix/suffix/total)?
4. **Identify the Identity Element**: What value should you return when a query is completely out of bounds (disjoint)?
5. **Determine Update Nature**: Are updates on single indices (Point Update) or entire subarrays (Range Update)?
6. **Decide if Lazy Propagation is Required**: If there are range updates, allocate a `lazy` array and implement a `push` helper.
7. **Write the Build Step**: Set up recursive division of ranges and post-order merging.
8. **Write the Query Step**: Resolve the three overlap cases: Disjoint (identity), Subset (return value), Intersect (recurse and merge).
9. **Write the Update Step**: Remember to implement the `push` operation at the start of both `query` and `update` calls if using Lazy Propagation.
10. **Allocate Memory**: Allocate \(4n\) elements for the tree structure.

---

## PART 9 — Project Connections

This project uses Segment Trees for various range search applications. You can reference actual implementations in the following files:
* [LFG_LLG.cpp](file:///d:/data-structure/SegmentTree/LFG_LLG.cpp) - Uses `SegmentTreeMax` to find Left First Greater and Left Last Greater.
* [LFS_LLS.cpp](file:///d:/data-structure/SegmentTree/LFS_LLS.cpp) - Uses `SegmentTreeMin` to find Left First Smaller and Left Last Smaller.
* [RFG_RLG.cpp](file:///d:/data-structure/SegmentTree/RFG_RLG.cpp) - Uses `SegmentTreeMax` to find Right First Greater and Right Last Greater.
* [RFS_RLS.cpp](file:///d:/data-structure/SegmentTree/RFS_RLS.cpp) - Uses `SegmentTreeMin` to find Right First Smaller and Right Last Smaller.

---

## PART 10 — Self-Test Problems (no spoilers)

Work through the 10-step checklist yourself on each before looking up solutions:

- **Easy**: Range Sum Query - Mutable (LeetCode 307); Range Minimum Query.
- **Medium**: Range GCD Queries; Queue Reconstruction by Height; Count of Smaller Numbers After Self (LeetCode 315).
- **Hard**: Range Maximum Subarray Sum (GSS1 on SPOJ); Rectangle Area II (LeetCode 850 - Sweep-line with Segment Tree); Block Placement Queries (LeetCode 3161).
