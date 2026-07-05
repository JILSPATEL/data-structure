# Array And K

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
3
```

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

    cout << arr[k-1] << '\n';

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

        System.out.println(arr[k-1]);
    }
}
```

---

## Python

```python
n,k = map(int,input().split())

arr = list(map(int,input().split()))

print(arr[k-1])
```

---

## Common Mistakes

- Using arr[k] instead of arr[k-1]
- Confusing 0-index and 1-index

---

## OA Notes

Very common in:

- Sliding Window
- Binary Search
- Prefix Sum
- Kth Element
- Heap Questions
