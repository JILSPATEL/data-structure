# Single String Input

## Input

```text
hello
```

## C++

```cpp
#include <bits/stdc++.h>
using namespace std;

/*
 * Single String Input
 */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    cout << s.length() << '\n';

    return 0;
}
```

## Java

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String s = sc.next();

        System.out.println(s.length());
    }
}
```

## Python

```python
s = input().strip()

print(len(s))
```

## Example

Input

```text
hello
```

Output

```text
5
```