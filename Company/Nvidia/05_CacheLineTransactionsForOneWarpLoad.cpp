/*
Problem: Count Distinct Cache Lines

Description:
A GPU warp contains 32 threads, and each thread requests a 4-byte
word from memory.

The memory controller operates on 128-byte cache lines. Multiple
threads accessing different addresses within the same cache line
can share a single memory transaction.

Given the memory addresses requested by the threads, count the
number of distinct cache lines accessed.

Approach:
1. Each cache line contains 128 bytes.
2. For every memory address, calculate its cache line index
   using address / 128.
3. Insert each cache line index into an unordered_set to avoid
   counting the same cache line multiple times.
4. Return the number of distinct cache lines in the set.

Example:
Input:
4
0 4 64 128

Output:
2

Explanation:
Addresses 0, 4, and 64 belong to cache line 0.
Address 128 belongs to cache line 1.

Therefore, the total number of distinct cache lines is 2.

Time Complexity: O(N) on average
Space Complexity: O(N)
*/

#include <bits/stdc++.h>
using namespace std;

int countTransactions(vector<long long>& addresses) {
    unordered_set<long long> lines;
    for(long long address:addresses){
        lines.insert(address/128);
    }
    return lines.size();
}

int main() {
    int n;
    cin >> n;

    vector<long long> addresses(n);

    for (int i = 0; i < n; i++) {
        cin >> addresses[i];
    }

    cout << countTransactions(addresses) << endl;

    return 0;
}