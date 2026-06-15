# Integer And String

## Input

```text
5
hello
```

## C++

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {

    int n;
    string s;

    cin >> n;
    cin >> s;

    cout << n << " " << s << '\n';
}
```

## Java

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        String s = sc.next();

        System.out.println(n + " " + s);
    }
}
```

## Python

```python
n = int(input())
s = input().strip()

print(n, s)
```

## Example

Input

```text
5
hello
```

Output

```text
5 hello
```