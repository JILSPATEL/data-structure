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
    string t = s;
    reverse(t.begin(), t.end());
    return s == t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    vector<string> ans;

    while (t--) {
        string s;
        cin >> s;

        ans.push_back(
            palindrome(s) ? "YES" : "NO"
        );
    }

    for (string x : ans)
        cout << x << '\n';

    return 0;
}
```

## Java

```java
import java.util.*;

public class Main {

    static boolean palindrome(String s) {
        return s.equals(
            new StringBuilder(s).reverse().toString()
        );
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();

        List<String> ans = new ArrayList<>();

        while (t-- > 0) {
            String s = sc.next();

            ans.add(
                palindrome(s) ? "YES" : "NO"
            );
        }

        for (String x : ans)
            System.out.println(x);
    }
}
```

## Python

```python
t = int(input())

ans = []

for _ in range(t):
    s = input().strip()

    ans.append(
        "YES" if s == s[::-1]
        else "NO"
    )

for x in ans:
    print(x)
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