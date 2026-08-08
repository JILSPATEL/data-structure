/**
 * Problem: Survived Robots Healths
 * 
 * Description:
 * We are given robots with positions, healths, and directions.
 * Robots move either left (L) or right (R). When two robots collide:
 * 
 * - The robot with smaller health gets destroyed.
 * - The robot with larger health loses 1 health.
 * - If both have equal health → both are destroyed.
 * 
 * Goal:
 * Return the healths of robots that survive, in original order.
 * 
 * ------------------------------------------------------------
 * Approach 1: Sorting + Stack Simulation
 * ------------------------------------------------------------
 * 1. Store all robot data in a struct:
 *    (position, health, direction, original index)
 * 
 * 2. Sort robots based on position
 *    → ensures we process collisions in correct order
 * 
 * 3. Use a stack:
 *    → stores indices of robots moving right ('R')
 * 
 * 4. Traverse robots:
 *    - If current robot is moving left ('L'),
 *      check collision with stack top (which is 'R')
 * 
 *    Collision Cases:
 *      a) top.health < curr.health
 *         → pop stack, curr loses 1 health
 * 
 *      b) top.health > curr.health
 *         → top loses 1 health, curr destroyed
 * 
 *      c) equal
 *         → both destroyed
 * 
 * 5. If current robot survives → push into stack
 * 
 * 6. Build result using original indices
 * 
 * ------------------------------------------------------------
 * Time Complexity: O(n log n)
 *   - Sorting dominates
 * 
 * Space Complexity: O(n)
 *   - Stack + auxiliary arrays
 */

class Solution {
public:
    struct Robot {
        int pos;
        int health;
        char dir;
        int idx;
    };

    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int n = positions.size();
        vector<Robot> robots(n);

        // Step 1: Store robot details
        for(int i = 0; i < n; i++){
            robots[i] = {positions[i], healths[i], directions[i], i};
        }

        // Step 2: Sort by position
        sort(robots.begin(), robots.end(), [](Robot &a, Robot &b) {
            return a.pos < b.pos;
        });

        stack<int> st; // stores indices of robots

        // Step 3: Process robots
        for(int i = 0; i < n; i++){
            int currHealth = robots[i].health;
            char currDir = robots[i].dir;

            // Step 4: Handle collisions
            while(!st.empty() && robots[st.top()].dir == 'R' && currDir == 'L'){
                int topIdx = st.top();

                if(robots[topIdx].health < currHealth){
                    currHealth--;
                    st.pop();
                }
                else if(robots[topIdx].health > currHealth){
                    robots[topIdx].health--;
                    currHealth = 0;
                    break;
                }
                else{
                    st.pop();
                    currHealth = 0;
                    break;
                }
            }

            // Step 5: If survives, push into stack
            if(currHealth > 0){
                robots[i].health = currHealth;
                st.push(i);
            }
        }

        // Step 6: Store survivors in result array
        vector<int> res(n, 0);
        while(!st.empty()){
            int i = st.top();
            st.pop();
            res[robots[i].idx] = robots[i].health;
        }

        // Step 7: Collect final answer
        vector<int> result;
        for(int i = 0; i < n; i++){
            if(res[i] > 0){
                result.push_back(res[i]);
            }
        }

        return result;
    }
};