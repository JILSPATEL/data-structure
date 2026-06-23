# Array With Queries

## Input Format

```text
n
array
q
query1
query2
...
queryq
```

## Example Input

```text
5
10 20 30 40 50
3
0
2
4
```

## Example Output

```text
10
30
50
```

---

## C++

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> arr(n);

    for(int i = 0; i < n; i++)
        cin >> arr[i];

    int q;
    cin >> q;

    vector<int> ans;

    while(q--) {

        int idx;
        cin >> idx;

        ans.push_back(arr[idx]);
    }

    for(int x : ans)
        cout << x << '\n';

    return 0;
}
```

---

## Java

```java
import java.util.*;

public class Main {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();

        int[] arr = new int[n];

        for(int i=0;i<n;i++)
            arr[i]=sc.nextInt();

        int q = sc.nextInt();

        List<Integer> ans = new ArrayList<>();

        while(q-- > 0) {

            int idx = sc.nextInt();

            ans.add(arr[idx]);
        }

        for(int x : ans)
            System.out.println(x);
    }
}
```

---

## Python

```python
n = int(input())

arr = list(map(int,input().split()))

q = int(input())

ans = []

for _ in range(q):

    idx = int(input())

    ans.append(arr[idx])

for x in ans:
    print(x)
```

---

## Common Mistakes

- Confusing value and index
- Using 1-index when query is 0-index
- Printing during query loop when OA expects final output

---

## OA Notes

Appears in:
- Prefix Sum
- Segment Tree
- Fenwick Tree
- Range Query Problems