# String With Spaces

## Input

```text
hello world from interview
```

## C++

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    getline(cin, s);

    cout << s.length() << '\n';
}
```

## Java

```java
import java.io.*;

public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader br =
            new BufferedReader(new InputStreamReader(System.in));

        String s = br.readLine();

        System.out.println(s.length());
    }
}
```

## Python

```python
s = input()

print(len(s))
```

## Example

Input

```text
hello world
```

Output

```text
11
```