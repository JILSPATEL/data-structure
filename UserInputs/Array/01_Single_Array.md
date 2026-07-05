# Single Array

## Input Format

```text
n
a1 a2 a3 ... an
```

## Example Input

```text
5
1 2 3 4 5
```

## Example Output

```text
15
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

    long long sum = 0;

    for(int x : arr)
        sum += x;

    cout << sum << '\n';

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

        for(int i = 0; i < n; i++)
            arr[i] = sc.nextInt();

        long sum = 0;

        for(int x : arr)
            sum += x;

        System.out.println(sum);
    }
}
```

---

## Python

```python
n = int(input())

arr = list(map(int, input().split()))

print(sum(arr))
```

---

## Common Mistakes

- Forgetting to read n
- Using int instead of long long
- Assuming array is multiline

---

## OA Notes

Most common pattern.

```text
n
array
```
