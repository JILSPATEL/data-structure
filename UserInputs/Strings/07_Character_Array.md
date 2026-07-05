# Character Array

## Input

```text
abcdef
```

## C++

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {

    string s;
    cin >> s;

    vector<char> arr;

    for(char c:s)
        arr.push_back(c);

    cout << arr.size();
}
```

## Java

```java
import java.util.*;

public class Main {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        String s = sc.next();

        char[] arr = s.toCharArray();

        System.out.println(arr.length);
    }
}
```

## Python

```python
s = input().strip()

arr = list(s)

print(len(arr))
```

## Example

Input

```text
abcdef
```

Output

```text
6
```