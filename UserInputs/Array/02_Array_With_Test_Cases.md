# Array With Test Cases

## Input Format

```text
t
n
array
n
array
...
```

## Example Input

```text
2
5
1 2 3 4 5
3
10 20 30
```

## Example Output

```text
15
60
```

---

## C++

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {

    int t;
    cin >> t;

    vector<long long> ans;

    while(t--) {

        int n;
        cin >> n;

        long long sum = 0;

        for(int i = 0; i < n; i++) {

            int x;
            cin >> x;

            sum += x;
        }

        ans.push_back(sum);
    }

    for(long long x : ans)
        cout << x << '\n';

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

        int t = sc.nextInt();

        List<Long> ans = new ArrayList<>();

        while(t-- > 0) {

            int n = sc.nextInt();

            long sum = 0;

            for(int i = 0; i < n; i++)
                sum += sc.nextInt();

            ans.add(sum);
        }

        for(long x : ans)
            System.out.println(x);
    }
}
```

---

## Python

```python
t = int(input())

ans = []

for _ in range(t):

    n = int(input())

    arr = list(map(int, input().split()))

    ans.append(sum(arr))

for x in ans:
    print(x)
```

---

## Common Mistakes

- Printing inside loop when OA expects all outputs together
- Forgetting t test cases
- Reusing previous array

---

## OA Notes

Most frequent OA format.

```text
t
test_case_1
test_case_2
```
