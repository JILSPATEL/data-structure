# Multiple Test Cases

## Input

```text
3
madam
hello
racecar
```

## C++

```cpp
#include <bits/stdc++.h>
using namespace std;

bool palindrome(string s) {
    string t=s;
    reverse(t.begin(),t.end());
    return s==t;
}

int main() {

    int t;
    cin >> t;

    while(t--) {

        string s;
        cin >> s;

        cout << (palindrome(s) ? "YES" : "NO") << '\n';
    }
}
```

## Java

```java
import java.util.*;

public class Main {

    static boolean palindrome(String s) {

        String rev =
            new StringBuilder(s).reverse().toString();

        return s.equals(rev);
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();

        while(t-- > 0) {

            String s = sc.next();

            System.out.println(
                palindrome(s) ? "YES" : "NO"
            );
        }
    }
}
```

## Python

```python
t = int(input())

for _ in range(t):

    s = input().strip()

    print(
        "YES" if s == s[::-1]
        else "NO"
    )
```

## Example

Input

```text
3
madam
hello
racecar
```

Output

```text
YES
NO
YES
```