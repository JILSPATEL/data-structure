# 🧠 Universal DP on Strings — One Mental Model

> Not templates. Not memorization. Just ONE way to think.

---

## 🔷 Step 1: Define the State

```
dp[i][j] = answer for s1[0...i-1] and s2[0...j-1]
```

👉 Always think in terms of **prefixes**.

---

## 🔷 Step 2: Visualize the Grid

```
        j →
      ""  a   b   c
i   ----------------
↓ "" | 0   0   0   0
  a  | 0   ?   ?   ?
  b  | 0   ?   ?   ?
  c  | 0   ?   ?   ?
```

Each cell depends on:

```
↖ dp[i-1][j-1]  (diagonal)
↑ dp[i-1][j]    (up)
← dp[i][j-1]    (left)
```

---

## 🔷 Step 3: The Only Real Decision

At every cell `(i, j)`:

### ✅ If characters match

```
s1[i-1] == s2[j-1]
→ move diagonally ↖
```

---

### ❌ If characters don’t match

👉 This defines the problem.

---

## 🔥 4 Problem Types (Covers Almost Everything)

---

### 1️⃣ Maximization (LCS type)

```
dp[i][j] = max(
    dp[i-1][j],
    dp[i][j-1]
)
```

🧠 Choose the best path.

---

### 2️⃣ Substring (Contiguous)

```
dp[i][j] = 0
```

🧠 Chain breaks → reset.

---

### 3️⃣ Counting (Distinct subsequences)

```
dp[i][j] = dp[i-1][j-1] + dp[i-1][j]
```

🧠 Count all possible ways.

---

### 4️⃣ Minimization (Edit distance)

```
dp[i][j] = 1 + min(
    dp[i-1][j],
    dp[i][j-1],
    dp[i-1][j-1]
)
```

🧠 Choose cheapest operation.

---

## 🧠 Final Universal Thinking Template

```
for i:
  for j:

    if match:
        use diagonal ↖

    else:
        if MAX problem:
            max(↑, ←)

        if MIN problem:
            1 + min(↑, ←, ↖)

        if COUNT problem:
            (↖ + ↑)

        if SUBSTRING:
            0
```

---

## 🎯 Identify Problem Type Quickly

| Question               | Type          |
| ---------------------- | ------------- |
| longest / maximum      | LCS           |
| substring / contiguous | reset         |
| number of ways         | counting      |
| minimum operations     | edit distance |

---

## 🔥 One-Line Memory Trick

```
MATCH → ↖

NO MATCH →
  MAX → max(↑, ←)
  MIN → 1 + min(↑, ←, ↖)
  COUNT → add paths
  SUBSTRING → 0
```

---

## 🚀 Key Insight

👉 Stop memorizing problems.
👉 Just decide: **What do I do on mismatch?**

That’s the whole game.

---
Happy Coding 🚀
