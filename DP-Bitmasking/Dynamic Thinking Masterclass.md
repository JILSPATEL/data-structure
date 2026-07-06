# Dynamic Programming — A Complete Masterclass

This is not a list of patterns to memorize. It's a method for *deriving* the solution to any DP problem from first principles. Every section follows the same ten-step lens:

1. How to recognize DP applies
2. How to choose the state
3. Why that state (and not another)
4. How to derive the recurrence
5. How to find base cases
6. How to size the DP table
7. Fill order
8. Memoization vs tabulation
9. Space optimization
10. The general pattern this problem represents

---

## PART 0 — The Recognition Lens (recap + sharpened)

A problem is solvable with DP when:

- **Choices exist.** At each "stage," you pick among a small number of options.
- **Optimal substructure.** The best solution to the whole problem is built from best solutions to sub-problems (not just *some* solution — the *best* one). This is what makes greedy fail and DP work: with DP you don't assume locally-best choices are globally best, you actually compute and compare.
- **Overlapping subproblems.** The naive recursion recomputes identical subproblems many times.

The practical test: **write the brute-force recursion first.** Define `f(parameters)` = answer to the problem restricted to those parameters. Write the recursion purely in terms of "try every choice, recurse, combine." Then ask: do recursive calls repeat? If yes → memoize → you have DP. If no repeats (each call has genuinely distinct, non-recurring parameters) → it's just recursion/divide-and-conquer, not DP.

This single habit — **always write brute-force recursion before thinking about tables** — is the single highest-leverage skill in this entire subject. Tables are just a *memory layout* for a recursion you already understand.

---

## PART 1 — Foundations: Climbing Stairs

> Ways to climb `n` stairs, taking 1 or 2 steps at a time.

**1. Recognition.** "Number of ways to reach n" with constrained moves (1 or 2 steps) → choices (which step size) + the remaining staircase after a choice is the *same kind* of problem, smaller. That's optimal substructure for a counting problem.

**2/3. State.** Define `f(n)` = number of ways to climb a staircase of height `n`. Why is `n` alone enough to describe the state? Because the *only* thing that affects your future choices is how many steps remain — not how you got there. This is the key test for state design: **a state is sufficient if, given it, you can determine all future possibilities without knowing the past.** This property is sometimes called the "Markov" property of DP states.

**4. Recurrence.** Your first move is either 1 step or 2 steps.
- If you take 1 step, you have `n-1` steps left: `f(n-1)` ways to finish.
- If you take 2 steps, you have `n-2` steps left: `f(n-2)` ways to finish.

These two cases are mutually exclusive and cover everything, so:
```
f(n) = f(n-1) + f(n-2)
```
Notice *why* it's a sum and not a max: the question asks "how many ways," so we **count** every distinct path → sum branches. (If the question asked "minimum cost to climb," you'd take a **min/max** over the branches instead. The recurrence's combination operator — sum, min, max, OR, AND — is dictated entirely by what the problem asks for. This is a crucial, often-missed point: people memorize "DP recurrences add things" — false. They combine using whatever operator answers the question.)

**5. Base cases.** `f(0) = 1` (one way to be "done" — do nothing). `f(1) = 1` (only one move possible). Base cases come from where the recursion **can no longer recurse** — the smallest inputs for which you can answer directly without invoking `f` again.

**6. Table size.** State has one parameter `n`, ranging `0..N` → a 1D array `dp[0..N]`. **Rule: the dimensionality of your table = the number of independent parameters in your state.**

**7. Fill order.** `f(n)` depends on `f(n-1)` and `f(n-2)` — smaller indices. So fill left to right, 0 up to N. **Rule: fill order must respect dependency — compute a cell only after every cell it depends on is already computed.**

**8. Memoization vs Tabulation.**
- *Memoization* (top-down): write the natural recursion, cache results in a dict/array. Best when: the *reachable* state space is much smaller than the full table (sparse), or when the recursion structure is easier to think about than an iteration order.
- *Tabulation* (bottom-up): fill the array iteratively in dependency order. Best when: you need every state anyway, you want to avoid recursion-stack overhead/depth limits, or you want to space-optimize afterward.

For climbing stairs, both work; tabulation is more natural here since every `f(0..n)` is needed anyway.

```python
# Memoization
def climb_memo(n, cache={}):
    if n <= 1: return 1
    if n in cache: return cache[n]
    cache[n] = climb_memo(n-1, cache) + climb_memo(n-2, cache)
    return cache[n]

# Tabulation
def climb_tab(n):
    dp = [0]*(n+1)
    dp[0] = dp[1] = 1
    for i in range(2, n+1):
        dp[i] = dp[i-1] + dp[i-2]
    return dp[n]
```

**9. Space optimization.** Look at the recurrence: `dp[i]` only ever needs `dp[i-1]` and `dp[i-2]`. You never need anything further back. **Rule: if `dp[i]` depends only on a fixed-size window of previous rows/indices, you can collapse the table to just that window.**

```python
def climb_opt(n):
    a, b = 1, 1   # a = f(i-2), b = f(i-1)
    for _ in range(2, n+1):
        a, b = b, a+b
    return b
```

**10. Pattern name:** **Linear / 1D DP.** Identify it by: a single integer parameter describing "how much of the input have I consumed," and a recurrence depending on a small fixed window of earlier states.

---

## PART 2 — More 1D DP: sharpening "what is the state"

### House Robber
> Houses in a row, each with money. Can't rob two adjacent houses. Maximize total money.

**Recognition:** at each house, a binary choice (rob / skip) with a constraint linking *adjacent* choices → classic DP-with-choice signature (as opposed to climbing stairs, which had no "value," only a count).

**State:** `dp[i]` = max money obtainable considering houses `0..i`. Why does `i` alone suffice? Because once you fix "considering houses up to i," the only thing that matters for what comes next is the *best achievable value*, not *which specific houses* you robbed — the constraint ("not adjacent") only cares about the *immediately preceding* choice, so it folds naturally into "i-1 vs i-2."

**Recurrence:** at house `i`, two choices:
- Skip house `i`: best is `dp[i-1]`
- Rob house `i`: get `nums[i]` + best up to `i-2` (can't use `i-1`): `nums[i] + dp[i-2]`

```
dp[i] = max(dp[i-1], nums[i] + dp[i-2])
```

This is the **same shape** as climbing stairs (`dp[i]` from `dp[i-1]`, `dp[i-2]`) but the combinator is `max` (optimization question) instead of `+` (counting question), and one branch is weighted by `nums[i]`. Seeing this structural echo — *same dependency shape, different combinator* — is exactly the transferable skill.

**Base cases:** `dp[0] = nums[0]`. `dp[1] = max(nums[0], nums[1])`.

**Table size:** 1D, size `n`.

**Space optimization:** again only needs last two values → O(1) with two rolling variables.

### Maximum Subarray (Kadane's Algorithm)
> Find contiguous subarray with the largest sum.

**Recognition (a subtler one):** "best subarray ending exactly at index i" is a well-defined sub-problem, and the best subarray ending at `i` either extends the best one ending at `i-1`, or starts fresh at `i`.

**State:** `dp[i]` = max sum of a subarray **ending at index i** (not "using the first i elements" — note the difference! This is an important state-design lesson: sometimes "ending at i" is a more useful state than "using up to i," because it captures contiguity directly).

**Recurrence:**
```
dp[i] = max(nums[i], dp[i-1] + nums[i])
//Either start a new subarray at i, or extend the previous best.
```
**Base case:** `dp[0] = nums[0]`.

**Answer:** `max(dp)` over all i — note the *table* answers "ending at i," but the *problem* asks for the best over all ending points, so the final answer is a max-reduction over the table, not just `dp[n-1]`. This distinction (state ≠ final answer; final answer is often a function *over* the state array) trips up beginners constantly — always ask "is my final answer dp[n], or some aggregate over the whole dp array?"

**Space optimization:** O(1), only need previous value (Kadane's classic form).

---

## PART 3 — 2D DP: Grids

### Unique Paths
> Robot at top-left of an `m x n` grid, moves only right or down, count paths to bottom-right.

**Recognition:** two-dimensional position, choices (right/down) at each cell, "count the ways" phrasing.

**State:** `dp[i][j]` = number of ways to reach cell `(i, j)` from the start. **Why two dimensions?** Because position requires two independent coordinates to describe, and the count of ways to reach a cell depends on *both* coordinates jointly — you cannot collapse it into one number without losing information.

**Recurrence:** to arrive at `(i,j)`, your last move was either from above `(i-1,j)` or from the left `(i,j-1)`:
```
dp[i][j] = dp[i-1][j] + dp[i][j-1]
```

**Base cases:** `dp[0][j] = 1` for all j (only one way along the top row — keep going right). `dp[i][0] = 1` for all i (only one way down the left column).

**Table size:** `m x n`, directly matching the grid.

**Fill order:** row by row, left to right (or column by column) — any order where `(i-1,j)` and `(i,j-1)` are filled before `(i,j)`.

**Space optimization:** `dp[i][j]` only needs the row above and the current row being built → collapse to a **1D rolling array** of size `n`:
```python
def unique_paths(m, n):
    dp = [1]*n
    for i in range(1, m):
        for j in range(1, n):
            dp[j] += dp[j-1]   # dp[j] currently holds "row above" value before update
    return dp[-1]
```
This is the general lesson: **whenever `dp[i][j]` only depends on row `i-1` and row `i` (not older rows), you can drop one full dimension.**

### Minimum Path Sum
Same grid shape, but now minimize a *cost* sum. Identical recurrence shape, swap `+` for `min`:
```
dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])
```
Notice again: **the skeleton (which cells you depend on) comes from the problem's movement rules; the combinator (`+`, `min`, `max`, count) comes from what's being asked.** Once you separate these two concerns, every grid DP problem becomes a variation on the same template.

**Pattern name:** **Grid DP.** Recognize by: movement on a 2D grid with restricted directions, optimize/count over paths.

---

## PART 4 — String DP

This is where 2D state really starts to feel necessary rather than just convenient — because now `i` and `j` index into **two different sequences**.

### Longest Common Subsequence (LCS)
> Given strings `A` (length m) and `B` (length n), find the length of the longest subsequence common to both.

**Recognition:** comparing two sequences, asking for an optimal-length *matching* — strong 2-sequence DP signal. The brute force ("try keeping or skipping each character of A and B") clearly recomputes the same `(i,j)` prefix pairs.

**State:** `dp[i][j]` = length of LCS of `A[0..i)` and `B[0..j)` (first i chars of A, first j chars of B). **Why both i and j?** Because progress through A and progress through B are *independent* — you can't reduce "how far you've consumed A and B" to a single number, since either string could be ahead of the other.

**Recurrence — derive it by asking "what are my choices at the last characters `A[i-1]` and `B[j-1]`?"**
- If `A[i-1] == B[j-1]`: this character *can* be part of the common subsequence. Take it, and add 1 to the best answer for the strings *without* this last character on both sides:
  ```
  dp[i][j] = 1 + dp[i-1][j-1]
  ```
- If `A[i-1] != B[j-1]`: this pair of characters cannot both be in the LCS together. So the LCS of `A[0..i)` and `B[0..j)` is the best of: drop the last char of A, or drop the last char of B:
  ```
  dp[i][j] = max(dp[i-1][j], dp[i][j-1])
  ```

This "look at the last element, decide whether it can be used" approach is **the** master technique for sequence DP — you will reuse this reasoning in Edit Distance, LIS, Knapsack, and beyond.

**Base cases:** `dp[0][j] = 0` for all j, `dp[i][0] = 0` for all i — an empty prefix has an LCS of length 0 with anything.

**Table size:** `(m+1) x (n+1)` — note the `+1`: row/column 0 represent "empty prefix," which is why base cases live at index 0 rather than needing special-casing inside the loop.

**Fill order:** row by row (or column by column), since `dp[i][j]` depends only on `dp[i-1][j-1]`, `dp[i-1][j]`, `dp[i][j-1]` — all "earlier" in a top-left-to-bottom-right sweep.

```python
def lcs(A, B):
    m, n = len(A), len(B)
    dp = [[0]*(n+1) for _ in range(m+1)]
    for i in range(1, m+1):
        for j in range(1, n+1):
            if A[i-1] == B[j-1]:
                dp[i][j] = 1 + dp[i-1][j-1]
            else:
                dp[i][j] = max(dp[i-1][j], dp[i][j-1])
    return dp[m][n]
```

**Space optimization:** only the previous row and current row are ever touched → reduce to two 1D arrays of size `n+1` (or one array with care about overwrite order).

### Edit Distance
> Minimum operations (insert/delete/replace) to convert string A into string B.

**State:** same shape — `dp[i][j]` = edit distance between `A[0..i)` and `B[0..j)`.

**Recurrence — again, examine the last characters:**
- If `A[i-1] == B[j-1]`: no operation needed on this pair: `dp[i][j] = dp[i-1][j-1]`.
- Else, you must do *something*. Three options, take the cheapest:
  - Replace `A[i-1]` with `B[j-1]`: `1 + dp[i-1][j-1]`
  - Delete `A[i-1]`: `1 + dp[i-1][j]`
  - Insert `B[j-1]` into A: `1 + dp[i][j-1]`
  ```
  dp[i][j] = min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]) + 1
  ```

**Base cases:** `dp[i][0] = i` (delete all i chars), `dp[0][j] = j` (insert all j chars).

This is *structurally identical* to LCS (same table shape, same dependency triangle) — only the combinator and the "match" branch differ. Once you've internalized LCS, Edit Distance is "LCS with a different payoff function."

### Longest Palindromic Subsequence
This is the same idea as LCS, but cleverly applied to a **string and its own reverse** — `LPS(s) = LCS(s, reverse(s))`. This is a good moment to notice: **recognizing that a new problem reduces to an old one you've already solved is itself a core DP skill**, not a separate technique.

It's also commonly solved directly with `dp[i][j]` = LPS within substring `s[i..j]`, which is your bridge into the next pattern: **Interval DP**.

**Pattern name so far:** **2-Sequence / String DP.** Recognize by: two strings/sequences being compared or transformed into each other; state = a pair of prefix lengths; recurrence built by examining the *last* elements of each.

---

## PART 5 — The Knapsack Family

This family is about **choices over a set of items, subject to a capacity constraint.** It is the single most-tested DP family in interviews.

### 0/1 Knapsack
> `n` items, each with weight `w[i]` and value `v[i]`. Capacity `W`. Maximize value without exceeding capacity. Each item used at most once.

**Recognition:** explicit "include or exclude" decision per item + a numeric constraint (capacity) that choices consume → the textbook knapsack signature. Whenever you see "subset of items," "at most once," "capacity/budget/weight limit," think knapsack.

**State:** `dp[i][c]` = max value achievable using the first `i` items with capacity `c` remaining. **Why two dimensions?** Because the decision for item `i` depends on how much capacity is *left*, and capacity isn't determined just by `i` — it depends on what you chose before. So capacity must be tracked explicitly as its own state dimension. This is the central new idea of the whole knapsack family: **the constraint itself becomes part of the state.**

**Recurrence — examine item `i` (the "last" item under consideration), exactly like LCS examined the last character:**
- Don't take item `i`: `dp[i][c] = dp[i-1][c]`
- Take item `i` (only valid if `w[i] <= c`): `dp[i][c] = v[i] + dp[i-1][c - w[i]]`

Take the better of the two:
```
dp[i][c] = dp[i-1][c]                                  if w[i] > c
dp[i][c] = max(dp[i-1][c], v[i] + dp[i-1][c-w[i]])     otherwise
```

**Base cases:** `dp[0][c] = 0` for all c (no items → 0 value). `dp[i][0] = 0` for all i (no capacity → 0 value).

**Table size:** `(n+1) x (W+1)`.

**Fill order:** by increasing `i`, and for each `i`, any order over `c` (since `dp[i][*]` only depends on `dp[i-1][*]`).

**Space optimization:** `dp[i]` only depends on `dp[i-1]` → collapse to **one 1D array of size W+1**, BUT you must iterate `c` from **high to low** when collapsing, otherwise you'd overwrite `dp[c - w[i]]` before using its "previous row" value, accidentally allowing item `i` to be used twice (turning 0/1 knapsack into unbounded knapsack by mistake). This is one of the most common silent bugs in DP code — **always ask: does my space-optimized loop order accidentally let me reuse a value I already overwrote?**

```python
def knapsack01(weights, values, W):
    n = len(weights)
    dp = [0]*(W+1)
    for i in range(n):
        for c in range(W, weights[i]-1, -1):   # high to low!
            dp[c] = max(dp[c], values[i] + dp[c-weights[i]])
    return dp[W]
```

### Subset Sum / Partition Equal Subset Sum
"Can a subset sum to exactly target T?" is **0/1 Knapsack with a boolean combinator (OR) instead of max**, weight = value = the number itself, capacity = T.
```
dp[i][c] = dp[i-1][c] OR (c >= nums[i] AND dp[i-1][c-nums[i]])
```
Same skeleton. This is the proof that knowing the *skeleton* (which previous cells you depend on) is more valuable than knowing the *specific formula* — the formula is just "skeleton + correct combinator for this question."

### Unbounded Knapsack / Coin Change
> Items can be used **unlimited** times. (E.g., Coin Change: min coins to make amount, or number of ways to make amount.)

**Key difference from 0/1:** since an item can be reused, when you "take" item `i`, you stay at row `i` (you may take it again), not row `i-1`:
```
dp[i][c] = max(dp[i-1][c], v[i] + dp[i][c-w[i]])   <-- note: dp[i], not dp[i-1], in the "take" branch
```

**Space-optimized (1D), the loop direction flips** compared to 0/1 knapsack — now you iterate `c` **low to high**, *because* you want to allow reuse of the same item within the same pass:
```python
def coin_change_min(coins, amount):
    dp = [float('inf')]*(amount+1)
    dp[0] = 0
    for coin in coins:
        for c in range(coin, amount+1):   # low to high!
            dp[c] = min(dp[c], dp[c-coin] + 1)
    return dp[amount] if dp[amount] != float('inf') else -1
```

**Loop-order rule, stated generally (memorize the reasoning, not the rule):**
- 0/1 (each item once) → inner loop over capacity goes **high → low**.
- Unbounded (item reusable) → inner loop over capacity goes **low → high**.
- *Counting combinations vs permutations* (e.g., "number of ways to make amount" where order doesn't matter, vs "number of ways" where order *does* matter, like Climbing-Stairs-with-arbitrary-coin-sizes) depends on whether the **outer loop is over coins or over amount** — outer-loop-over-coins avoids counting the same multiset in different orders; outer-loop-over-amount counts ordered sequences. This is worth pausing on and testing yourself with small examples (coins=[1,2], amount=3) by hand if it ever confuses you in a contest.

**Pattern name:** **Knapsack DP.** Recognize by: a set of items, a binary or repeatable "use it or not" decision, and an explicit numeric constraint that becomes a DP dimension.

---

## PART 6 — Longest Increasing Subsequence (LIS)

> Given an array, find the length of the longest strictly increasing subsequence.

**Recognition:** "longest subsequence satisfying an order condition" — note this is *not* comparing two sequences (so it's not the LCS shape) — it's about *one* sequence and a relation between *pairs of elements within it*.

**State:** `dp[i]` = length of the longest increasing subsequence **ending exactly at index i**. (Same "ending at i" idea as Kadane's — when the natural state "using first i elements" doesn't carry enough information, try "ending at i" instead. Why does this work here? Because whether you can *extend* a subsequence depends on its **last element's value**, which is exactly what "ending at i" pins down.)

**Recurrence:** to end an increasing subsequence at `i`, look at every earlier index `j < i`; if `nums[j] < nums[i]`, you could extend that subsequence:
```
dp[i] = 1 + max( dp[j] for all j < i where nums[j] < nums[i] )
        (or 1, if no such j exists)
```

**Base case:** every `dp[i]` is at least 1 (the element alone).

**Table size:** 1D, size n — **but the recurrence requires an inner loop over all `j < i`**, giving O(n²) time, not O(n) like our earlier 1D examples. This is an important lesson: **1D state does not imply O(n) time** — the *transition* cost matters too. Total complexity = (number of states) × (cost to compute each state's transition).

**Final answer:** `max(dp)` — again, an aggregate over the table, not `dp[n-1]`.

```python
def lis_length(nums):
    n = len(nums)
    dp = [1]*n
    for i in range(n):
        for j in range(i):
            if nums[j] < nums[i]:
                dp[i] = max(dp[i], dp[j]+1)
    return max(dp)
```

**Optimized O(n log n) — the "patience sorting" idea:**
Maintain an array `tails`, where `tails[k]` = the smallest possible tail value of an increasing subsequence of length `k+1` found so far. For each new number, binary-search for where it belongs in `tails` and replace/extend.

This is worth understanding conceptually even though it isn't a classic "table DP": it's still founded on the *same* optimal substructure idea (you only need the smallest tail for each length — a greedy-with-proof compression of the O(n²) DP state), but it stores far less information by being clever about *what's worth remembering*. This is a preview of an advanced DP skill: **sometimes you can prove that most of your DP table is redundant and compress it.**

**Pattern name:** **Single-sequence subsequence DP**, distinguished from LCS by being about *one* array and a relation (here, `<`) between pairs.

---

## PART 7 — Interval DP

> The hallmark phrasing: "given a sequence, partition or process it in *one contiguous range at a time*, combining results from splitting the range at some point."

### Matrix Chain Multiplication
> Matrices `A1, A2, ..., An` with given dimensions. Find the minimum number of scalar multiplications to compute the product, by choosing parenthesization order.

**Recognition:** the cost of multiplying a *range* of matrices depends on **where you place the last split** — and once you split at `k`, the two halves `[i,k]` and `[k+1,j]` are *independent subproblems of the same kind*. This "split a range into two independent ranges" structure is the defining signature of Interval DP.

**State:** `dp[i][j]` = minimum cost to compute the product of matrices `i` through `j`. **Why this state?** Because once you know the optimal cost for *any* fully-specified contiguous range, you can build up larger ranges from smaller ones — and a range is fully described by its two endpoints, hence 2D state over (start, end) rather than over (position, something else).

**Recurrence — try every possible split point k inside the range:**
```
dp[i][j] = min over k in [i, j-1] of:
              dp[i][k] + dp[k+1][j] + cost_of_combining(i, k, j)
```
(For matrix chains, `cost_of_combining` is `dims[i-1]*dims[k]*dims[j]`.)

**Base case:** `dp[i][i] = 0` — a single matrix needs no multiplication.

**Table size:** `n x n` (only the upper triangle, `i <= j`, is meaningful).

**Fill order — this is the new idea in this pattern:** you cannot fill row by row or column by column, because `dp[i][j]` depends on `dp[i][k]` and `dp[k+1][j]` for *k strictly between* `i` and `j` — i.e., it depends on **shorter ranges**, not "earlier rows." So you must fill **by increasing range length**:
```python
def matrix_chain(dims):
    n = len(dims) - 1   # number of matrices
    dp = [[0]*n for _ in range(n)]
    for length in range(2, n+1):              # range length, smallest first
        for i in range(0, n-length+1):
            j = i + length - 1
            dp[i][j] = float('inf')
            for k in range(i, j):
                cost = dp[i][k] + dp[k+1][j] + dims[i]*dims[k+1]*dims[j+1]
                dp[i][j] = min(dp[i][j], cost)
    return dp[0][n-1]
```

**General rule for Interval DP fill order:** iterate the **interval length from small to large**, and within each length, iterate the start index. This guarantees every smaller sub-interval you depend on is already computed.

**Complexity:** O(n²) states × O(n) per transition (the k-loop) = O(n³) — typical for interval DP.

### Palindrome Partitioning II (min cuts to partition a string into palindromes)
Same skeleton: `dp[i]` = min cuts for `s[0..i]`, and within it you need a helper "is `s[j+1..i]` a palindrome" table — itself an interval DP (`isPal[i][j]` filled by increasing length, with the recurrence `isPal[i][j] = (s[i]==s[j]) and isPal[i+1][j-1]`). This shows interval DP often appears as a **building block inside another DP**, not just as the top-level problem.

**Pattern name:** **Interval DP.** Recognize by: "optimal way to process/combine/partition a contiguous range," with a recurrence that **splits the range at a variable point k**. Fill order is always by increasing interval length.

---

## PART 8 — Tree DP

> The structure is a tree instead of a line or grid. The defining new skill: **the "fill order" becomes a traversal order (post-order DFS) instead of a loop over indices.**

### Maximum Independent Set on a Tree (a.k.a. "House Robber III")
> Each node has a value. Pick a subset of nodes, no two adjacent (parent-child), maximize sum.

**Recognition:** tree structure + a constraint linking parent and children + "maximize over a subset" → tree DP.

**State — here's the key new idea:** for tree DP, a single number per node is often *not enough*, because what you can do at the parent depends on what *state the child ended up in*. So the state often has an extra dimension representing "the situation at this subtree's root":

`dp[node][0]` = best answer for the subtree rooted at `node`, **given node is NOT selected**
`dp[node][1]` = best answer for the subtree rooted at `node`, **given node IS selected**

**Why split into two states instead of just "best for this subtree"?** Because the parent's decision depends on whether *this* node was picked (adjacency constraint) — so the parent needs both possibilities available to choose correctly, not just whichever was bigger. This is the tree-DP version of "the state must contain everything the next decision needs to know."

**Recurrence (derived by post-order: solve children completely before combining at the parent):**
```
dp[node][0] = sum over children c of  max(dp[c][0], dp[c][1])   # node not picked: each child free to be picked or not
dp[node][1] = node.value + sum over children c of  dp[c][0]      # node picked: children CANNOT be picked
```

**Base case:** a leaf node: `dp[leaf][0] = 0`, `dp[leaf][1] = leaf.value`.

**Table size:** conceptually `dp[node][2]` — number of nodes × 2 states. In code this is usually just two values returned from a recursive function rather than a literal array.

**Fill order:** **post-order DFS** — you must fully solve all children before you can compute the parent. This is the tree analogue of "fill by increasing interval length": both are really saying "solve dependencies before dependents," just expressed differently because the underlying domain (line / grid / range / tree) differs.

```python
def rob_tree(root):
    def dfs(node):
        if not node: return (0, 0)   # (not_picked, picked)
        l0, l1 = dfs(node.left)
        r0, r1 = dfs(node.right)
        not_picked = max(l0,l1) + max(r0,r1)
        picked = node.val + l0 + r0
        return (not_picked, picked)
    return max(dfs(root))
```

**Memo vs tabulation for trees:** memoization (recursive DFS) is almost always the natural and simplest choice for tree DP, since trees don't have an obvious "iterate by index" order the way arrays do; tabulation would require first computing a topological/post-order list of nodes manually, which is just reimplementing DFS by hand. Use recursion here.

**Pattern name:** **Tree DP.** Recognize by: a tree structure + need to combine answers from children to answer for a node, often needing 2+ states per node to capture "what the parent needs to know."

---

## PART 9 — Bitmask DP

> Used when the state needs to remember **a subset of a small set of items** (n typically ≤ ~20, since `2^n` must be tractable).

### Traveling Salesman Problem (TSP)
> Visit all `n` cities exactly once, minimize total travel cost, return to start.

**Recognition:** "must visit/use every element exactly once, order/subset matters, n is small (≤ ~20)" is the unmistakable bitmask-DP signature. The brute-force "try all orders" is `n!`; the key insight that unlocks DP is: **what matters about your past isn't *which order* you visited cities in, only *which set* you've visited and *where you currently are*.**

**State:** `dp[mask][i]` = minimum cost to have visited exactly the set of cities in `mask`, currently standing at city `i` (where `i` is itself in `mask`). **Why this state?** Because "mask" alone isn't enough (you also need to know where you currently are, to know the cost of your next move), and "current city" alone isn't enough (you need to know what's left unvisited). The *pair* (visited set, current position) is the minimal sufficient summary of the past — exactly satisfying the "Markov" requirement from Part 1, just in a more complex form.

**Recurrence:** to arrive at state `(mask, i)`, you came from some city `j` that's in `mask` but isn't `i`, where `mask` without `i` was already the visited set:
```
dp[mask][i] = min over j in mask, j != i, (mask without i) has j set:
                 dp[mask without i][j] + cost(j, i)
```

**Base case:** `dp[{start}][start] = 0` (mask containing only the start city, standing at start city, cost 0).

**Table size:** `2^n x n` — this is *why* n must be small: `2^20 ≈ 10^6`, times `n=20`, times an O(n) transition = roughly `4×10^8`, borderline but feasible; `2^25` would not be.

**Fill order:** by increasing **popcount (number of set bits) of mask** — a state with k bits set depends only on states with k-1 bits set. This is conceptually identical to "fill by increasing interval length" in Interval DP: **fill in order of increasing "subproblem size,"** however "size" is defined for this domain.

```python
def tsp(n, cost):
    FULL = (1 << n) - 1
    dp = [[float('inf')] * n for _ in range(1 << n)]
    dp[1][0] = 0   # start at city 0, only city 0 visited
    for mask in range(1 << n):
        for i in range(n):
            if dp[mask][i] == float('inf') or not (mask & (1<<i)):
                continue
            for j in range(n):
                if mask & (1 << j): continue
                nmask = mask | (1 << j)
                dp[nmask][j] = min(dp[nmask][j], dp[mask][i] + cost[i][j])
    return min(dp[FULL][i] + cost[i][0] for i in range(n))
```

**Pattern name:** **Bitmask DP.** Recognize by: small n, "visit/assign/use every element," and the realization that *which subset* (not which order) is what matters for the future.

---

## PART 10 — Digit DP

> Used for: "count numbers in `[L, R]` satisfying some digit-based property" (digit sum, no repeated digits, contains a specific pattern, etc.)

**Recognition:** the phrase "count numbers up to N with property P about their digits," especially when N can be huge (up to 10^18), ruling out iterating every number directly.

**Core idea:** count numbers from 0 to N by **building them digit by digit**, left to right, and at each digit deciding what to place — but you must track whether you're still "bounded" by N's digits so far (i.e., could exceeding N happen if you're not careful), plus whatever digit-property state the problem needs.

**State:** `dp[pos][tight][extra_state...]`
- `pos`: which digit position you're currently filling (processed so far)
- `tight`: boolean — does the prefix built so far exactly equal N's prefix? (If yes, your next digit is capped at N's digit at this position. If no — you've already placed a smaller digit somewhere — you're free to place any digit 0-9 from here on.)
- `extra_state`: whatever the problem needs to track (e.g., running digit sum, whether you've used a digit already, parity, etc.)

**Why `tight` matters and why it must be part of the state:** it's exactly the same "sufficiency" test from Part 1 — without knowing whether you're still bounded by N, you cannot correctly decide the legal range for the *next* digit, so the recursion would be wrong without it.

**Recurrence (conceptual):** at position `pos` with `tight=True`, you can place any digit `d` from `0` to `N[pos]`; placing exactly `N[pos]` keeps `tight=True` for the next position, placing anything smaller sets `tight=False` from then on (fully free). Sum/count over all valid `d` the results of the recursive call at `pos+1` with the updated `tight` and updated `extra_state`.

**Base case:** `pos == len(N)` — you've placed every digit; return 1 if `extra_state` satisfies the target property, else 0.

**Table size:** `len(N) x 2 x (range of extra_state)` — typically small (length of N is ≤ ~18 digits), which is why digit DP is efficient even for astronomically large N — you're not iterating numbers, you're iterating digit positions.

This is best implemented as **memoized recursion** (top-down), not tabulation, because the `tight` branch genuinely behaves like a tree of choices that's natural to express recursively, and many `(pos, extra_state)` combinations with `tight=False` get reused heavily (hence cache only on `(pos, extra_state)` when `tight=False`, since `tight=True` only ever occurs along a single path).

```python
def count_with_property(N_str, target_sum):
    n = len(N_str)
    from functools import lru_cache

    @lru_cache(maxsize=None)
    def dp(pos, tight, digit_sum):
        if digit_sum > target_sum: 
            return 0
        if pos == n:
            return 1 if digit_sum == target_sum else 0
        limit = int(N_str[pos]) if tight else 9
        total = 0
        for d in range(0, limit+1):
            total += dp(pos+1, tight and (d == limit), digit_sum + d)
        return total

    return dp(0, True, 0)
```

To answer "count in `[L, R]`": compute `f(R) - f(L-1)` using the same helper on each bound — a standard prefix-counting trick.

**Pattern name:** **Digit DP.** Recognize by: counting numbers up to (possibly huge) N with a digit-based constraint.

---

## PART 11 — The General Framework (apply this to ANY new problem)

When you face an unfamiliar problem, run this checklist in order:

1. **Can I phrase it as a recursive decision process?** What is the "current situation," and what choices do I have from here?
2. **Write the brute-force recursion.** `f(parameters)` = answer for this sub-situation, defined purely by "try each choice, recurse on the resulting smaller situation, combine results."
3. **Identify the combinator** dictated by the question: count → sum; optimize → min/max; existence → OR/AND.
4. **Check for overlap.** Do different choice-sequences lead to the *same* `f(parameters)` call? If yes, DP applies — cache it.
5. **Minimize the state.** Ask: "is there redundant information in my parameters that I could drop while still uniquely determining the future?" (e.g., "ending at i" vs "using first i," "visited set" vs "visited order"). Smaller/simpler state = faster, simpler DP.
6. **Derive base cases** from where recursion bottoms out naturally (empty input, single element, smallest valid range).
7. **Determine table dimensions** = number of independent parameters in your minimized state.
8. **Determine fill order** from the dependency direction in your recurrence: smaller index, shorter interval, fewer set bits, smaller subtree, less-traversed digit position — always solve dependencies before dependents.
9. **Choose memo vs tabulation:** sparse/irregular reachable states or recursive-feeling structure (trees, digit DP, branching with pruning) → memoize. Dense/regular, every state needed anyway, or want to space-optimize → tabulate.
10. **Look for space optimization** by asking: does `dp[current]` only depend on a bounded recent window (last row, last k entries)? If so, collapse the table — but double check loop direction so you don't accidentally reuse data you shouldn't (the 0/1 vs unbounded knapsack lesson).

---

## PART 12 — Self-Test Problems (no spoilers — for you to apply the framework above)

Work through the 10-step checklist yourself on each before looking anything up:

- **Easy:** Min Cost Climbing Stairs; Decode Ways; Maximum Product Subarray
- **2D / Knapsack:** Target Sum; Combination Sum IV (ordered vs unordered counting!); Coin Change II
- **String:** Longest Palindromic Substring (interval DP); Distinct Subsequences; Wildcard/Regex Matching (2-sequence DP)
- **LIS family:** Russian Doll Envelopes (2D LIS — sort + LIS trick); Number of LIS
- **Interval:** Burst Balloons; Minimum Cost to Merge Stones
- **Tree:** Binary Tree Cameras; Longest Path with Same Value in a Tree
- **Bitmask:** Smallest Sufficient Team; Partition to K Equal Sum Subsets
- **Digit DP:** Numbers with Repeated Digits; Count Numbers with Unique Digits

For each, before coding: (a) state the recognition signal, (b) propose a state, (c) justify why that state is sufficient, (d) derive the recurrence by examining the "last" decision, (e) find base cases, (f) decide table size/dimension, (g) decide fill order, (h) pick memo or tabulation, (i) check for space optimization.

---

*This document is meant to be revisited. The patterns above are not a checklist to match against — they are the natural conclusions of applying the same six-step reasoning (state → why sufficient → recurrence by examining the last decision → base case → dimensions → fill order) to different problem shapes. If you internalize the reasoning process rather than the named patterns, novel problems in interviews/contests will feel like "which shape is this closest to," and you'll derive the rest yourself.*
