# Patience Sorting

Patience Sorting is a simple and powerful algorithm for finding the length of the Longest Increasing Subsequence (LIS) in an array. The idea is inspired by the card game "patience" (also known as solitaire), where cards are placed into piles according to specific rules.

## Why is it useful?

- It finds the LIS length in O(n log n) time.
- It is much faster than the simple O(n^2) dynamic programming approach for large arrays.
- It is easy to understand once you know the pile-building rules.

## How it works

We maintain several piles of numbers. Each pile is built so that the top card (the last number in the pile) is always as small as possible.

### Rules for placing a number

For each number in the input array:

1. Look for the leftmost pile whose top number is greater than or equal to the current number.
2. If such a pile exists, place the current number on top of that pile.
3. If no such pile exists, start a new pile with the current number.

This process does not build the actual LIS sequence directly, but the number of piles at the end equals the length of the LIS.

## Example

Input array: `[3, 1, 2, 5, 4, 7]`

Start with no piles.

- Process `3`:
  - No pile exists, create pile 1: `[3]`
  - Piles: `[3]`

- Process `1`:
  - The top of pile 1 is `3`, which is >= `1`.
  - Place `1` on top of pile 1: `[1]`
  - Piles: `[1]`

- Process `2`:
  - The top of pile 1 is `1`, which is < `2`.
  - No existing pile has top >= `2`, so create pile 2: `[2]`
  - Piles: `[1]`, `[2]`

- Process `5`:
  - The top of pile 1 is `1` (< 5), top of pile 2 is `2` (< 5).
  - No pile top is >= `5`, so create pile 3: `[5]`
  - Piles: `[1]`, `[2]`, `[5]`

- Process `4`:
  - The tops are `1`, `2`, and `5`.
  - The leftmost pile with top >= `4` is pile 3 (`5`).
  - Place `4` on top of pile 3: `[4]`
  - Piles: `[1]`, `[2]`, `[4]`

- Process `7`:
  - The tops are `1`, `2`, and `4`.
  - No pile top is >= `7`, so create pile 4: `[7]`
  - Piles: `[1]`, `[2]`, `[4]`, `[7]`

At the end, we have 4 piles, so the length of the LIS is `4`.

One possible increasing subsequence of length 4 is `[1, 2, 4, 7]`.

## Why the number of piles equals LIS length

- Each pile represents a potential increasing subsequence.
- When we place a number on a pile, we keep the pile's top number as small as possible.
- A smaller top number gives more opportunity to extend that subsequence later.
- The minimum number of piles needed to place all numbers equals the length of the longest increasing subsequence.

## Efficient implementation

Instead of storing all piles, we can store only the top values of the piles in a list called `tops`.

- For each number `x`:
  - Find the first position in `tops` where the value is >= `x`.
  - Replace that value with `x` if found.
  - If not found, append `x` to `tops`.

This search can be done with binary search in O(log n) time.

### Pseudocode

```
function patienceSortingLIS(arr):
    tops = []
    for x in arr:
        i = lower_bound(tops, x)
        if i == len(tops):
            tops.append(x)
        else:
            tops[i] = x
    return len(tops)
```

`lower_bound(tops, x)` returns the first index `i` where `tops[i] >= x`.

## Time and space complexity

- Time: O(n log n)
- Space: O(n)

## Summary

- Patience Sorting is an algorithm for computing the LIS length quickly.
- It builds piles by placing each number on the leftmost pile with a top card >= the number.
- The number of piles at the end is the LIS length.
- Using `tops` and binary search makes the algorithm efficient and easy to implement.

## Quick tip for beginners

Think of `tops` as the smallest possible last values of increasing subsequences of each length. If `tops` has size 4, that means there is an increasing subsequence of length 4.
