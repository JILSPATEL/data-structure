# Array Of Pairs

## Input Format

```text
n
a b
a b
a b
```

## Example Input

```text
3
1 10
2 20
3 30
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

    vector<pair<int,int>> arr(n);

    for(int i=0;i<n;i++) {

        cin >> arr[i].first
            >> arr[i].second;
    }

    cout << arr[0].first + arr[0].second;

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

        int[][] arr = new int[n][2];

        for(int i=0;i<n;i++) {

            arr[i][0]=sc.nextInt();
            arr[i][1]=sc.nextInt();
        }

        System.out.println(
            arr[0][0] + arr[0][1]
        );
    }
}
```

---

## Python

```python
n = int(input())

pairs = []

for _ in range(n):

    a,b = map(int,input().split())

    pairs.append((a,b))

print(
    pairs[0][0] + pairs[0][1]
)
```

---

## Common Mistakes

- Using separate arrays unnecessarily
- Forgetting tuple unpacking

---

## OA Notes

Used in:

- Intervals
- Coordinates
- Graph Edges
- Scheduling Problems

```text
n
u v
u v
u v
```