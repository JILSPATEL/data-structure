# String Matrix

## Input

```text
3 3
abc
def
ghi
```

## C++

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {

    int n,m;
    cin >> n >> m;

    vector<string> mat(n);

    for(int i=0;i<n;i++)
        cin >> mat[i];

    cout << mat[1][1];
}
```

## Java

```java
import java.util.*;

public class Main {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int m = sc.nextInt();

        String[] mat = new String[n];

        for(int i=0;i<n;i++)
            mat[i] = sc.next();

        System.out.println(mat[1].charAt(1));
    }
}
```

## Python

```python
n,m = map(int,input().split())

mat = [input().strip() for _ in range(n)]

print(mat[1][1])
```

## Example

Input

```text
3 3
abc
def
ghi
```

Output

```text
e
```