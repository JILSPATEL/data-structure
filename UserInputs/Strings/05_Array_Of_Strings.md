# Array Of Strings

## Input

```text
4
apple
banana
mango
orange
```

## C++

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {

    int n;
    cin >> n;

    vector<string> arr(n);

    for(int i=0;i<n;i++)
        cin >> arr[i];

    for(string s : arr)
        cout << s << " ";

    return 0;
}
```

## Java

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();

        String[] arr = new String[n];

        for(int i=0;i<n;i++)
            arr[i] = sc.next();

        for(String s : arr)
            System.out.print(s + " ");
    }
}
```

## Python

```python
n = int(input())

arr = [input().strip() for _ in range(n)]

print(*arr)
```

## Example

Input

```text
3
abc
def
ghi
```

Output

```text
abc def ghi
```