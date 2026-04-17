# 📦 Heap Templates (Min Heap & Max Heap)

This guide provides reusable templates for **Min Heap** and **Max Heap** in both **C++** and **Python**, along with examples.

---

## 🧠 What is a Heap?

A **heap** is a special tree-based data structure that satisfies:

- **Min Heap** → smallest element at the top
- **Max Heap** → largest element at the top

---

# 🚀 C++ Templates

## 🔹 Min Heap (C++)

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    priority_queue<int, vector<int>, greater<int>> minHeap;

    minHeap.push(10);
    minHeap.push(5);
    minHeap.push(20);

    cout << minHeap.top() << endl; // 5

    minHeap.pop();

    cout << minHeap.top() << endl; // 10
}
```

---

## 🔹 Max Heap (C++)

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    priority_queue<int> maxHeap;

    maxHeap.push(10);
    maxHeap.push(5);
    maxHeap.push(20);

    cout << maxHeap.top() << endl; // 20

    maxHeap.pop();

    cout << maxHeap.top() << endl; // 10
}
```

## Min Heap (c++) For Multi Dimentional

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    pq.push({2, 100});
    pq.push({1, 200});
    pq.push({3, 50});

    while (!pq.empty()) {
        auto top = pq.top();
        cout << top.first << " " << top.second << endl;
        pq.pop();
    }
}
```
## Max Heap (c++) For Multi Dimentional

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    priority_queue<pair<int,int>> pq;

    pq.push({2, 100});
    pq.push({1, 200});
    pq.push({3, 50});

    while (!pq.empty()) {
        auto top = pq.top();
        cout << top.first << " " << top.second << endl;
        pq.pop();
    }
}
```
# 🔹 Custom Comparator (IMPORTANT 🔥)

## Min Heap based on second element (C++)

```cpp
#include <bits/stdc++.h>
using namespace std;

struct cmp {
    bool operator()(pair<int,int>& a, pair<int,int>& b) {
        return a.second > b.second; // min heap based on second
    }
};

int main() {
    priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> pq;

    pq.push({1, 100});
    pq.push({2, 50});
    pq.push({3, 200});

    while (!pq.empty()) {
        auto p = pq.top();
        cout << p.first << " " << p.second << endl;
        pq.pop();
    }
}
```

## 🔹 Lambda Comparator

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    auto cmp = [](pair<int,int>& a, pair<int,int>& b) {
        return a.second > b.second; // min heap based on second
    };

    priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);

    pq.push({1, 100});
    pq.push({2, 50});
    pq.push({3, 200});

    while (!pq.empty()) {
        auto p = pq.top();
        cout << p.first << " " << p.second << endl;
        pq.pop();
    }
}
```
---

# 🐍 Python Templates

## 🔹 Min Heap (Python)

```python
import heapq

min_heap = []

heapq.heappush(min_heap, 10)
heapq.heappush(min_heap, 5)
heapq.heappush(min_heap, 20)

print(min_heap[0])  # 5

heapq.heappop(min_heap)

print(min_heap[0])  # 10
```

---

## 🔹 Max Heap (Python)

```python
import heapq

max_heap = []

heapq.heappush(max_heap, -10)
heapq.heappush(max_heap, -5)
heapq.heappush(max_heap, -20)

print(-max_heap[0])  # 20

heapq.heappop(max_heap)

print(-max_heap[0])  # 10
```
## 🐍 Python (Tuples in Heap)

Python `heapq` automatically sorts tuples **lexicographically**:
- First element
- Then second element (if tie)

---

## 🔹 Min Heap (Default Behavior)

```python
import heapq

heap = []

heapq.heappush(heap, (2, 100))
heapq.heappush(heap, (1, 200))
heapq.heappush(heap, (3, 50))

while heap:
    print(heapq.heappop(heap))
---

# 📊 Complexity

| Operation | Time |
|----------|------|
| Insert   | O(log n) |
| Delete   | O(log n) |
| Top      | O(1) |

---

# 🎯 Use Cases

- Priority Queue
- Top K elements
- Dijkstra’s Algorithm
- Scheduling problems
