# Two Strings

## Input

```text
hello
world
```

## C++

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {

    string s1, s2;

    cin >> s1 >> s2;

    cout << s1 + s2 << '\n';
}
```

## Java

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        String s1 = sc.next();
        String s2 = sc.next();

        System.out.println(s1 + s2);
    }
}
```

## Python

```python
s1 = input().strip()
s2 = input().strip()

print(s1 + s2)
```

## Example

Input

```text
hello
world
```

Output

```text
helloworld
```