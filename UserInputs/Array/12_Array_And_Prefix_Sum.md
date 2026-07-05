# Array And Prefix Sum

## Input Format

```text
n
array
```

## Example Input

```text
5
1 2 3 4 5
```

## Example Output

```text
1 3 6 10 15
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

    vector<long long> prefix(n);

    prefix[0] = arr[0];

    for(int i=1;i<n;i++)
        prefix[i] = prefix[i-1] + arr[i];

    for(long long x : prefix)
        cout << x << " ";

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
            arr[i] = sc.nextInt();

        long[] prefix = new long[n];

        prefix[0] = arr[0];

        for(int i=1;i<n;i++)
            prefix[i] = prefix[i-1] + arr[i];

        for(long x : prefix)
            System.out.print(x + " ");
    }
}
```

---

## Python

```python
n = int(input())

arr = list(map(int,input().split()))

prefix = [0]*n

prefix[0] = arr[0]

for i in range(1,n):
    prefix[i] = prefix[i-1] + arr[i]

print(*prefix)
```

---

## Common Mistakes

- Forgetting prefix[0]
- Using int for large sums
- Starting loop from 0

---

## OA Notes

Must memorize.

Used in:

- Range Sum Query
- Sliding Window
- Difference Array
- Binary Search on Answer
- Segment Tree
- Competitive Programming

Formula:

```text
prefix[i] = prefix[i-1] + arr[i]
```

Range Sum:

```text
sum(l,r)

=
prefix[r] - prefix[l-1]
```