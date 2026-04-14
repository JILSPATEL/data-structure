/**
 * Problem: Circular Previous Smaller Element (PSE)
 * 
 * Find previous smaller element considering array circular.
 * If not found on left, search from end of array.
 * 
 * Example:
 * Input:  [5, 7, 1, 2, 6, 0]
 * Output: [0, 5, -1, 1, 2, -1]
 * 
 * Approaches:
 * 1. Extend array virtually (2*n traversal)
 * 2. Use monotonic increasing stack
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> circularPSE(vector<int>& nums) {
    int n = nums.size();
    vector<int> pse(n, -1);
    stack<int> st;

    for (int i = 0; i < 2 * n; i++) {
        int curr = nums[i % n];

        while (!st.empty() && st.top() >= curr) {
            st.pop();
        }

        if (i >= n && !st.empty()) {
            pse[i % n] = st.top();
        }

        st.push(curr);
    }

    return pse;
}

int main() {
    vector<int> v {5, 7, 1, 2, 6, 0};
    vector<int> res = circularPSE(v);

    cout << "Circular Previous Smaller Elements:\n";
    for (int x : res) cout << x << " ";
    cout << endl;
}