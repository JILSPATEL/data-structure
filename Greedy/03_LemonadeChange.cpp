/**
 * Problem: Lemonade Change
 * ------------------------------------------------------
 * Each lemonade costs $5.
 * Customers pay with 5, 10, or 20.
 * You must return correct change using available bills.
 *
 * ------------------------------------------------------
 * Approach:
 *
 * 1) Track count of $5 and $10 bills.
 * 2) For each customer:
 *    - If bill == 5 → no change needed
 *    - If bill == 10 → give one $5
 *    - If bill == 20:
 *         Prefer giving (10 + 5)
 *         Else give (5 + 5 + 5)
 *         Else return false
 *
 * Greedy Strategy:
 * - Always use larger bills first to save smaller ones
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * ------------------------------------------------------
 */

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {

        int five = 0;   // count of $5 bills
        int ten = 0;    // count of $10 bills

        for (int bill : bills) {

            if (bill == 5) {
                five++;
            }

            else if (bill == 10) {
                if (five == 0) return false;
                five--;
                ten++;
            }

            else { // bill == 20

                // Prefer using one 10 and one 5
                if (ten > 0 && five > 0) {
                    ten--;
                    five--;
                }
                // Otherwise use three 5s
                else if (five >= 3) {
                    five -= 3;
                }
                else {
                    return false;
                }
            }
        }

        return true;
    }
};