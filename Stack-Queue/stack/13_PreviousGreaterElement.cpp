/**
 * Problem: Previous Greater Element (PGE)
 * 
 * Given an array, for each element find the previous element
 * that is greater than it. If none exists, return -1.
 * 
 * Example:
 * Input:  [4, 8, 5, 2, 25]
 * Output: [-1, -1, 8, 5, -1]
 * 
 * Approaches:
 * 1. Brute Force: Check left side → O(n^2)
 * 2. Optimal (Monotonic Stack): Use decreasing stack → O(n)
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> previousGreaterElements(vector<int>& nums) {
    int n = nums.size();
    vector<int> pge(n, -1);
    stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && st.top() <= nums[i]) {
            st.pop();
        }

        if (!st.empty()) {
            pge[i] = st.top();
        }

        st.push(nums[i]);
    }

    return pge;
}

int main() {
    vector<int> v {4, 8, 5, 2, 25};
    vector<int> res = previousGreaterElements(v);

    cout << "Previous Greater Elements:\n";
    for (int x : res) cout << x << " ";
    cout << endl;
}