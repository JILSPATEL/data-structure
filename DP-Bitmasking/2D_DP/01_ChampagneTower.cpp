/**
 * Problem: Champagne Tower
 * --------------------------------
 * We pour some amount of champagne into the top glass of a triangular tower.
 * Each glass can hold at most 1 unit of champagne.
 *
 * If a glass overflows (i.e., champagne > 1), the extra amount is split equally
 * and poured into the two glasses directly below it:
 *   - bottom-left
 *   - bottom-right
 *
 * The structure looks like this:
 *
 *                (0,0)
 *              (1,0) (1,1)
 *           (2,0) (2,1) (2,2)
 *        ...
 *
 * Given:
 *   - poured      → total champagne poured into the top glass
 *   - query_row   → row index of the target glass
 *   - query_glass → glass index in that row
 *
 * Task:
 *   Return how much champagne is in the target glass.
 *   The value must be capped at 1.0 (because a glass cannot hold more than 1).
 *
 * ----------------------------------------------------
 * Approach: Top-Down Dynamic Programming (Memoization)
 * ----------------------------------------------------
 *
 * Let solve(poured, i, j) represent the amount of champagne reaching
 * the glass at position (i, j) before capping it to 1.
 *
 * Key Observations:
 * 1. Invalid states:
 *    - If i < 0, j < 0, or j > i → the glass does not exist.
 *
 * 2. Base case:
 *    - The top glass (0, 0) initially receives all the poured champagne.
 *
 * 3. Transition:
 *    - A glass (i, j) receives champagne from:
 *        a) the upper-left glass (i - 1, j - 1)
 *        b) the upper-right glass (i - 1, j)
 *
 *    - If an upper glass contains more than 1 unit, only the overflow
 *      (value - 1) is passed down.
 *
 *    - The overflow is split equally between the two lower glasses:
 *
 *          overflow = (upper_value - 1) / 2
 *
 *    - If the upper glass has ≤ 1 unit, it contributes nothing downward.
 *
 * 4. Memoization:
 *    - dp[i][j] stores the computed champagne amount for glass (i, j)
 *      to avoid recomputation.
 *
 * 5. Final Answer:
 *    - The result is min(1.0, amount), since a glass cannot exceed capacity.
 *
 * Time Complexity:
 *   O(query_row²) — each state (i, j) is computed once.
 *
 * Space Complexity:
 *   O(query_row²) — DP table storage.
 */

class Solution {
public:
    double dp[101][101];

    double solve(int poured, int i, int j) {
        // Invalid glass positions
        if (i < 0 || j < 0 || i < j) {
            return 0.0;
        }

        // Top glass gets all poured champagne
        if (i == 0 && j == 0) {
            return poured;
        }

        // Return memoized result if already computed
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        // Champagne coming from upper-left and upper-right glasses
        double upLeft  = (solve(poured, i - 1, j - 1) - 1) / 2.0;
        double upRight = (solve(poured, i - 1, j) - 1) / 2.0;

        // Only positive overflow contributes
        if (upLeft < 0) {
            upLeft = 0.0;
        }
        if (upRight < 0) {
            upRight = 0.0;
        }

        // Total champagne in current glass
        return dp[i][j] = upLeft + upRight;
    }

    double champagneTower(int poured, int query_row, int query_glass) {
        // Initialize DP table with -1 (uncomputed)
        for (int i = 0; i < 101; i++) {
            for (int j = 0; j < 101; j++) {
                dp[i][j] = -1;
            }
        }

        // Cap result to maximum glass capacity
        return min(1.0, solve(poured, query_row, query_glass));
    }
};
