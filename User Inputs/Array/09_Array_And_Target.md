# Array And Target

## Input Format

```text
n
array
target
```

## Example Input

```text
5
1 2 3 4 5
4
```

## Example Output

```text
YES
```

---

## C++

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {

    int n;
    cin >> n;

    vector<int> arr(n);

    for(int i=0;i<n;i++)
        cin >> arr[i];

    int target;
    cin >> target;

    bool found = false;

    for(int x : arr) {

        if(x == target) {

            found = true;
            break;
        }
    }

    cout << (found ? "YES" : "NO") << '\n';

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

        int n = sc.nextInt();

        int[] arr = new int[n];

        for(int i=0;i<n;i++)
            arr[i] = sc.nextInt();

        int target = sc.nextInt();

        boolean found = false;

        for(int x : arr) {

            if(x == target) {
                found = true;
                break;
            }
        }

        System.out.println(
            found ? "YES" : "NO"
        );
    }
}
```

---

## Python

```python
n = int(input())

arr = list(map(int,input().split()))

target = int(input())

found = False

for x in arr:
    if x == target:
        found = True
        break

print("YES" if found else "NO")
```

---

## Common Mistakes

- Forgetting to read target
- Comparing index with target
- Not breaking after finding answer

---

## OA Notes

Very common in:

- Linear Search
- Two Sum
- HashMap
- Binary Search