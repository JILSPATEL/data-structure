# Array And Window K

## Input Format

```text
n k
array
```

## Example Input

```text
5 3
1 2 3 4 5
```

## Example Output

```text
12
```

Explanation:

```text
1+2+3 = 6
2+3+4 = 9
3+4+5 = 12
```

Maximum = 12

---

## C++

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {

    int n,k;

    cin >> n >> k;

    vector<int> arr(n);

    for(int i=0;i<n;i++)
        cin >> arr[i];

    long long window = 0;

    for(int i=0;i<k;i++)
        window += arr[i];

    long long ans = window;

    for(int i=k;i<n;i++) {

        window += arr[i];
        window -= arr[i-k];

        ans = max(ans, window);
    }

    cout << ans << '\n';

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
        int k = sc.nextInt();

        int[] arr = new int[n];

        for(int i=0;i<n;i++)
            arr[i] = sc.nextInt();

        long window = 0;

        for(int i=0;i<k;i++)
            window += arr[i];

        long ans = window;

        for(int i=k;i<n;i++) {

            window += arr[i];
            window -= arr[i-k];

            ans = Math.max(ans, window);
        }

        System.out.println(ans);
    }
}
```

---

## Python

```python
n,k = map(int,input().split())

arr = list(map(int,input().split()))

window = sum(arr[:k])

ans = window

for i in range(k,n):

    window += arr[i]
    window -= arr[i-k]

    ans = max(ans, window)

print(ans)
```

---

## Common Mistakes

- Forgetting first window
- Using O(n*k)
- Wrong index i-k

---

## OA Notes

Most common Sliding Window template.

Appears in:

- Maximum Sum Subarray
- Fixed Window Problems
- Leetcode Easy/Medium