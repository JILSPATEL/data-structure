# String And Query

## Input

```text
abcdef
3
0
2
5
```

## C++

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {

    string s;
    cin >> s;

    int q;
    cin >> q;

    while(q--) {

        int idx;
        cin >> idx;

        cout << s[idx] << '\n';
    }
}
```

## Java

```java
import java.util.*;

public class Main {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        String s = sc.next();

        int q = sc.nextInt();

        while(q-- > 0) {

            int idx = sc.nextInt();

            System.out.println(s.charAt(idx));
        }
    }
}
```

## Python

```python
s = input().strip()

q = int(input())

for _ in range(q):

    idx = int(input())

    print(s[idx])
```

## Example

Input

```text
abcdef
3
0
2
5
```

Output

```text
a
c
f
```