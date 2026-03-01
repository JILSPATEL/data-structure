/**
 * Problem Description:
 * You are given a triangle array where each row has one more element than the previous row.
 * Starting from the top of the triangle, you can move only to adjacent numbers in the row
 * below. Your task is to find the minimum path sum from the top to the bottom of the triangle.
 *
 * Approach Explanation (Bottom-Up Dynamic Programming):
 * - Instead of starting from the top, we solve the problem from the bottom of the triangle.
 * - Each element in a row can move to two elements directly below it: 
 *   triangle[i+1][j] and triangle[i+1][j+1].
 * - For each element triangle[i][j], we add the minimum of these two possible paths.
 * - By doing this from the second-last row up to the first row, we accumulate the minimum
 *   path sums.
 * - Finally, triangle[0][0] will contain the minimum total path sum from top to bottom.
 *
 * Time Complexity:
 * - O(n^2), where n is the number of rows in the triangle.
 *
 * Space Complexity:
 * - O(1) extra space, since the triangle itself is modified to store the results.
 */
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        for (int i = n - 2; i >= 0; i--) {
            for (int j = 0; j < triangle[i].size(); j++) {
                triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);
            }
        }
        return triangle[0][0];
    }
};