# Array With Range Queries

## Input Format

```text
n
array
q
l r
l r
...
```

## Example Input

```text
5
1 2 3 4 5
3
0 2
1 3
2 4
```

## Example Output

```text
6
9
12
```

---

## C++

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {

    int n;
    cin >> n;

    vector<int> arr(n);

    for(int i=0;i<n;i++)
        cin >> arr[i];

    int q;
    cin >> q;

    vector<long long> ans;

    while(q--) {

        int l,r;
        cin >> l >> r;

        long long sum = 0;

        for(int i=l;i<=r;i++)
            sum += arr[i];

        ans.push_back(sum);
    }

    for(long long x : ans)
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

        List<Long> ans = new ArrayList<>();

        while(q-- > 0) {

            int l = sc.nextInt();
            int r = sc.nextInt();

            long sum = 0;

            for(int i=l;i<=r;i++)
                sum += arr[i];

            ans.add(sum);
        }

        for(long x : ans)
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

    l,r = map(int,input().split())

    ans.append(sum(arr[l:r+1]))

for x in ans:
    print(x)
```

---

## Common Mistakes

- Forgetting inclusive range
- Using r instead of r+1 in Python slice

---

## OA Notes

Brute Force version.

Optimized version uses:

- Prefix Sum
- Fenwick Tree
- Segment Tree