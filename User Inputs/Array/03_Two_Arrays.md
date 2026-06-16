# Two Arrays

## Input Format

```text
n
array1
m
array2
```

## Example Input

```text
5
1 2 3 4 5
5
10 20 30 40 50
```

## Example Output

```text
11
```

---

## C++

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {

    int n;
    cin >> n;

    vector<int> a(n);

    for(int i=0;i<n;i++)
        cin >> a[i];

    int m;
    cin >> m;

    vector<int> b(m);

    for(int i=0;i<m;i++)
        cin >> b[i];

    cout << a[0] + b[0] << '\n';

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

        int[] a = new int[n];

        for(int i=0;i<n;i++)
            a[i] = sc.nextInt();

        int m = sc.nextInt();

        int[] b = new int[m];

        for(int i=0;i<m;i++)
            b[i] = sc.nextInt();

        System.out.println(a[0] + b[0]);
    }
}
```

---

## Python

```python
n = int(input())
a = list(map(int,input().split()))

m = int(input())
b = list(map(int,input().split()))

print(a[0] + b[0])
```

---

## Common Mistakes

- Assuming same size arrays
- Forgetting second n/m

---

## OA Notes

Used in merge/intersection/two pointer questions.
