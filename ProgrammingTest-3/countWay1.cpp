/**
 * Count Ways to Make N Rupees (Easy Version)
 * 
 * Problem: Given N, find number of distinct ways to make N rupees using unlimited 2 and 3 rupee coins.
 * Order does NOT matter.
 * 
 * Constraints: 1 ≤ N ≤ 10^18, 1 ≤ T ≤ 100000
 * 
 * Sample Input:
 * 5
 * 1
 * 2
 * 3
 * 6
 * 7
 * 
 * Sample Output:
 * 0
 * 1
 * 1
 * 2
 * 1
 * 
 * Approach: 
 * Let x = number of 2-rupee coins, y = number of 3-rupee coins
 * We need to solve: 2x + 3y = N
 * The number of non-negative integer solutions is floor(N/6) + 1 for most cases,
 * but need to handle edge cases carefully.
 */

#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    
    while (T--) {
        long long N;
        cin >> N;
        
        // For equation 2x + 3y = N
        // The number of non-negative integer solutions is floor((N + 2) / 2) - ceil(max(0, N - 3k)/2) 
        // But simpler: count how many y (3-rupee coins) we can use
        // y can range from 0 to floor(N/3), and for each y, x = (N - 3y)/2 must be non-negative integer
        
        if (N <= 1) {
            cout << "0\n";
        } else {
            // Number of possible y values where (N - 3y) is non-negative and even
            // This equals floor(N/6) + 1 with some adjustments
            long long ways = (N / 6) + 1;
            
            // Adjust for cases where the pattern doesn't hold
            if (N % 2 == 1) {
                // For odd N, we need different calculation
                ways = ((N - 3) >= 0) ? ((N - 3) / 6) + 1 : 0;
            }
            
            cout << ways << "\n";
        }
    }
    
    return 0;
}