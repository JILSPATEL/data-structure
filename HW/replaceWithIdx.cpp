/*
Problem:
Given an array A of length n, construct an array B of the same length such that:

For each index i (0-based indexing), find the smallest index j such that:

"j > i" and "A[i] > A[j]"

If such a j exists, set B[i] = j (1-based indexing in the result).
If no such j exists, set B[i] = n (the array length in 1-based indexing).

Example:

Input:  A = [4, 7, 6, 5, 3, 8, 1]  
Output: B = [4, 2, 3, 4, 6, 6, 7]

*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> check(const vector<int> &a) {
    int n = a.size();
    vector<int> b(n, 0);
    for (int i = 0; i < n; i++) {
        b[i] = n; 
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[i]) {
                b[i] = j ;
                break;
            }
        }
    }
    return b;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> b = check(a);

    for (int i = 0; i < n; ++i) {
        cout << b[i] << " ";
    }
    cout << endl;

    return 0;
}
