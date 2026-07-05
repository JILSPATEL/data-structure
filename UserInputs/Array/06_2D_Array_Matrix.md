# 2D Array Matrix

## Input Format

```text
rows cols
matrix
```

## Example Input

```text
3 3
1 2 3
4 5 6
7 8 9
```

## Example Output

```text
5
```

---

## C++

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {

    int n,m;

    cin >> n >> m;

    vector<vector<int>> mat(n, vector<int>(m));

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin >> mat[i][j];

    cout << mat[1][1] << '\n';

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
        int m = sc.nextInt();

        int[][] mat = new int[n][m];

        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                mat[i][j]=sc.nextInt();

        System.out.println(mat[1][1]);
    }
}
```

---

## Python

```python
n,m = map(int,input().split())

mat = []

for _ in range(n):
    mat.append(
        list(map(int,input().split()))
    )

print(mat[1][1])
```

---

## Common Mistakes

- Swapping row and column
- Wrong nested loop order
- Using matrix[j][i]

---

## OA Notes

Most common matrix format.

```text
n m
row1
row2
...
rown
```