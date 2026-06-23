# Jagged Array

## Input Format

```text
n
size element1 element2 ...
size element1 element2 ...
```

## Example Input

```text
3
3 1 2 3
2 4 5
4 6 7 8 9
```

## Example Output

```text
1
```

---

## C++

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {

    int n;
    cin >> n;

    vector<vector<int>> arr(n);

    for(int i=0;i<n;i++) {

        int sz;
        cin >> sz;

        arr[i].resize(sz);

        for(int j=0;j<sz;j++)
            cin >> arr[i][j];
    }

    cout << arr[0][0] << '\n';

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

        int[][] arr = new int[n][];

        for(int i=0;i<n;i++) {

            int sz = sc.nextInt();

            arr[i] = new int[sz];

            for(int j=0;j<sz;j++)
                arr[i][j]=sc.nextInt();
        }

        System.out.println(arr[0][0]);
    }
}
```

---

## Python

```python
n = int(input())

arr = []

for _ in range(n):

    temp = list(map(int,input().split()))

    sz = temp[0]

    arr.append(temp[1:])

print(arr[0][0])
```

---

## Common Mistakes

- Assuming all rows same length
- Using rectangular matrix logic

---

## OA Notes

Popular in:
- Hackerrank Dynamic Array
- Variable Length Arrays
- Adjacency Lists