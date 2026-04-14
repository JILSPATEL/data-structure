/**
 * Problem: Previous Smaller Element (PSE)
 * 
 * Given an array, for each element find the previous element
 * that is smaller than it. If none exists, return -1.
 * 
 * Example:
 * Input:  [4, 8, 5, 2, 25]
 * Output: [-1, 4, 4, -1, 2]
 * 
 * Approaches:
 * 1. Brute Force: For each element, check left side → O(n^2)
 * 2. Optimal (Monotonic Stack): Use increasing stack → O(n)
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> previousSmallerElements(vector<int>& nums) {
    int n = nums.size();
    vector<int> pse(n, -1);
    stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && st.top() >= nums[i]) {
            st.pop();
        }

        if (!st.empty()) {
            pse[i] = st.top();
        }

        st.push(nums[i]);
    }

    return pse;
}

int main() {
    vector<int> v {4, 8, 5, 2, 25};
    vector<int> res = previousSmallerElements(v);

    cout << "Previous Smaller Elements:\n";
    for (int x : res) cout << x << " ";
    cout << endl;
}