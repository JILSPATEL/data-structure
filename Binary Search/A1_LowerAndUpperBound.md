# Lower Bound and Upper Bound (Binary Search)

In a **sorted array**, *lower bound* and *upper bound* are classic applications of **binary search**. They are widely used in competitive programming, system design, and STL-based solutions.

---

## 📌 Lower Bound

### 🔹 Definition

The **lower bound** of an element `x` is the **smallest index `i` such that `arr[i] >= x`**.

* If all elements are smaller than `x`, the lower bound is `n` (array size).
* Works only on **sorted arrays**.

### 🔹 Intuition

We want the **first position where `x` can be inserted** without breaking the sorted order.

### 🔹 Algorithm Explanation

1. Since the array is sorted, we apply **Binary Search**.
2. Initialize:

   * `low = 0`
   * `high = n - 1`
   * `ans = n` (default answer if not found)
3. While `low <= high`:

   * Compute `mid = (low + high) // 2`
   * Compare `arr[mid]` with `x`

#### Cases

* **Case 1: `arr[mid] >= x`**
  `mid` *can be* a valid answer.
  Update `ans = mid` and search the **left half** for a smaller index.

* **Case 2: `arr[mid] < x`**
  `mid` cannot be the answer.
  Eliminate the left half and search the **right half**.

4. Return `ans`.

---

### 🔹 Pseudocode (Lower Bound)

```text
function lower_bound(arr, n, x):
    low = 0
    high = n - 1
    ans = n

    while low <= high:
        mid = (low + high) // 2
        if arr[mid] >= x:
            ans = mid
            high = mid - 1
        else:
            low = mid + 1

    return ans
```

---

## 📌 Upper Bound

### 🔹 Definition

The **upper bound** of an element `x` is the **smallest index `i` such that `arr[i] > x`**.

* If no element is greater than `x`, the upper bound is `n`.
* Works only on **sorted arrays**.

### 🔹 Intuition

We want the **first position where an element strictly greater than `x` appears**.

### 🔹 Algorithm Explanation

1. Use **Binary Search** on the sorted array.
2. Initialize:

   * `low = 0`
   * `high = n - 1`
   * `ans = n`
3. While `low <= high`:

   * Compute `mid = (low + high) // 2`
   * Compare `arr[mid]` with `x`

#### Cases

* **Case 1: `arr[mid] > x`**
  `mid` *may be* the answer.
  Update `ans = mid` and search the **left half**.

* **Case 2: `arr[mid] <= x`**
  `mid` cannot be the answer.
  Eliminate the left half and search the **right half**.

4. Return `ans`.

---

### 🔹 Pseudocode (Upper Bound)

```text
function upper_bound(arr, n, x):
    low = 0
    high = n - 1
    ans = n

    while low <= high:
        mid = (low + high) // 2
        if arr[mid] > x:
            ans = mid
            high = mid - 1
        else:
            low = mid + 1

    return ans
```

---

## 📌 C++ STL Inbuilt Methods

C++ provides **ready-made functions** for both lower and upper bounds in the `<algorithm>` header.

### 🔹 Syntax

```cpp
#include <algorithm>

int idx1 = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
int idx2 = upper_bound(arr.begin(), arr.end(), x) - arr.begin();
```

### 🔹 What They Do

* `lower_bound()` → returns iterator to **first element >= x**
* `upper_bound()` → returns iterator to **first element > x**

If such an element does not exist, they return `arr.end()`.

---

## 📌 Example

```text
Array: [1, 2, 4, 4, 4, 6, 7]
x = 4

Lower Bound Index = 2  (first 4)
Upper Bound Index = 5  (first element > 4 → 6)
```

---

## 📌 Time & Space Complexity

| Method                | Time Complexity | Space Complexity |
| --------------------- | --------------- | ---------------- |
| Manual Binary Search  | O(log n)        | O(1)             |
| STL lower/upper_bound | O(log n)        | O(1)             |

---

## ✅ Summary

* **Lower Bound** → first index where `arr[i] >= x`
* **Upper Bound** → first index where `arr[i] > x`
* Both rely on **binary search** and work only on **sorted arrays**
* Prefer **STL methods** in C++ for cleaner and safer code

---

✨ Perfect for GitHub notes, interview prep, and competitive programming!
