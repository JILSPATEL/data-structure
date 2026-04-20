/**
 * Problem: Fractional Knapsack
 * ------------------------------------------------------
 * You are given:
 * - val[i] → value of ith item
 * - wt[i]  → weight of ith item
 * - capacity → maximum weight the knapsack can carry
 *
 * Goal:
 * Maximize total value by selecting items.
 * You CAN take fractional parts of items.
 *
 * ------------------------------------------------------
 * Approaches:
 *
 * 1) Brute Force (Not Practical)
 *    - Try all subsets and fractional combinations
 *    - Time Complexity: Exponential
 *
 * 2) Greedy Approach (Optimal)
 *    - Key Idea: Pick items with highest value/weight ratio first
 *    - Steps:
 *        a) Compute ratio = value / weight
 *        b) Sort items in descending order of ratio
 *        c) Pick full item if possible
 *        d) Otherwise pick fractional part
 *
 *    Why Greedy Works?
 *    - Because taking the highest ratio always gives maximum gain per unit weight
 *
 *    Time Complexity: O(n log n)
 *    Space Complexity: O(n)
 *
 * ------------------------------------------------------
 */

class Solution {
public:
    double fractionalKnapsack(vector<int>& val, vector<int>& wt, int capacity) {

        int n = val.size();

        // Store: {value/weight ratio, {value, weight}}
        vector<pair<double, pair<int, int>>> item;

        // Step 1: Calculate ratio for each item
        for (int i = 0; i < n; i++) {
            double ratio = (double)val[i] / wt[i];
            item.push_back({ratio, {val[i], wt[i]}});
        }

        // Step 2: Sort items by ratio in descending order
        sort(item.begin(), item.end(), greater<>());

        int remain = capacity;   // remaining capacity
        double total = 0.0;      // total value

        // Step 3: Pick items greedily
        for (auto &it : item) {

            double ratio = it.first;
            int value = it.second.first;
            int weight = it.second.second;

            // If we can take full item
            if (weight <= remain) {
                total += value;
                remain -= weight;
            }
            // Take fractional part
            else {
                total += ratio * remain;
                break;
            }
        }

        // Step 4: Return value rounded to 6 decimal places
        return round(total * 1e6) / 1e6;
    }
};