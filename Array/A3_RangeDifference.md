# Range Difference (Difference Array / Differential Array)

This note explains the Difference Array (a.k.a. Differential Array) technique for performing efficient range updates on arrays — commonly called "Range Update using Difference Array." It's useful when you have many operations that add a value to every element in a subarray [l, r].

**Idea**

- Maintain a helper array `D` (the difference array) such that the original array `A` can be recovered by taking prefix sums of `D`.
- For a range add operation "add `val` to A[l..r]" (0-based indices):
  - `D[l] += val`
  - `D[r+1] -= val` (if `r+1` is within bounds)
- After applying all range operations to `D`, compute the final `A` by doing a prefix-sum over `D`:
  - `A[i] = (i==0 ? D[0] : A[i-1] + D[i])`

This allows each range update to run in O(1), and all updates plus building the final array cost O(n + q) where `n` is array size and `q` is number of updates.

**Why it works (intuition)**

- `D[i]` stores how much `A[i]` changes relative to `A[i-1]`.
- Adding `val` at `D[l]` makes all positions from `l` onward increased by `val`.
- Subtracting `val` at `D[r+1]` cancels that increase starting from `r+1`, so only `l..r` see the net addition.

**Complexity**

- Single range update: O(1)
- Applying q updates and reconstructing array: O(n + q)
- Extra memory: O(n) for the difference array (can be done in-place if allowed).

**C++ example**

```cpp
#include <bits/stdc++.h>
using namespace std;

// Apply q range-add updates on an array of size n and return final array
vector<long long> applyRangeAdds(int n, const vector<tuple<int,int,long long>>& updates) {
    vector<long long> D(n+1, 0); // one extra to avoid bounds checks
    for (auto &u : updates) {
        int l, r; long long val;
        tie(l, r, val) = u; // assume 0-based inclusive l,r
        D[l] += val;
        if (r + 1 < n) D[r+1] -= val;
    }
    vector<long long> A(n);
    long long cur = 0;
    for (int i = 0; i < n; ++i) {
        cur += D[i];
        A[i] = cur;
    }
    return A;
}

int main() {
    int n = 5;
    // start with zeros; to support starting from a non-zero base array, initialize D accordingly
    vector<tuple<int,int,long long>> updates = {
        {1, 3, 2}, // add 2 to A[1..3]
        {2, 4, 3}, // add 3 to A[2..4]
    };
    auto res = applyRangeAdds(n, updates);
    for (auto x : res) cout << x << ' '; // output: 0 2 5 5 3
    cout << '\n';
}
```

**Compact update loop (using parallel vectors `a,b,k`)**

If updates are stored in parallel vectors `a`, `b`, and `k` (start, end, value), you can apply them directly to the difference array as:

```cpp
vector<long long> diff(n+1,0);
for(int i=0;i<a.size();i++){
    diff[a[i]]+=k[i];

    if(b[i]+1<n){
        diff[b[i]+1]-=k[i];
    }
}
```

This does the same as the `tie(l,r,val)` loop above: `diff[a[i]] += k[i]` adds `k[i]` from `a[i]` onwards, and `diff[b[i]+1] -= k[i]` cancels it after `b[i]`.
**Using with an initial array**

- If you have an existing array `A0`, you can build `D` by setting `D[0]=A0[0]` and `D[i]=A0[i]-A0[i-1]` for `i>0`. Then apply range updates on `D` and recover the final array with prefix sums.

**Common variants & uses**

- Range addition updates + point queries: After applying updates to `D`, compute prefix sum up to index `i` for the point query.
- Range addition updates + range sum queries: Use a Fenwick/segment tree on the final array, or maintain prefix sums of the final array.
- Difference arrays generalize easily to other operations (e.g., range assignment with careful handling, or difference of higher order sequences).

**Pitfalls**

- Indexing: be consistent with 0-based vs 1-based indices. For 1-based arrays increment/decrement positions accordingly.
- Bound checks: only apply `D[r+1] -= val` when `r+1` is within array bounds.
- Data types: use `long long` if values or number of operations can make sums large.

**Short example (manual)**

- n = 5, initial A = [0,0,0,0,0]
- update: add 2 to [1,3] → D changes: D[1]+=2, D[4]-=2
- update: add 3 to [2,4] → D changes: D[2]+=3, D[5]-=3 (out of bounds, ignored)
- D (first n elements) = [0,2,3,0,-2]
- Prefix sums → A = [0,2,5,5,3]

---

References: common competitive programming technique; useful for batched range updates when q is large compared to n.
