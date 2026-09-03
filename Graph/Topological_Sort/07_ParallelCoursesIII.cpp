/**
 * Problem: Parallel Courses III
 *
 * Description:
 * There are `n` courses. Each course takes a given number of months, and a
 * relation [u, v] means course `u` must be completed before course `v` starts.
 * Any courses whose prerequisites are complete can be taken in parallel.
 * Return the minimum number of months needed to finish every course.
 *
 * Intuition:
 * The finish time of a course is its duration plus the latest finish time of
 * all its prerequisites. Courses on independent paths run simultaneously, so
 * the total completion time is the maximum finish time among all courses.
 * A topological order guarantees that every prerequisite is processed before
 * its dependent course.
 *
 * Approach:
 * 1. Build the graph and calculate the indegree of every course.
 * 2. Add all courses with no prerequisites to a queue.
 * 3. Process courses in BFS topological order. For each course, calculate its
 *    finish time and use it to update the earliest start time of its neighbors.
 * 4. When a neighbor has no remaining prerequisites, add it to the queue.
 * 5. Return the maximum finish time.
 *
 * Example:
 * Input: n = 3, relations = [[1,3], [2,3]], time = [3,2,5]
 *
 * Courses 1 and 2 can run together. Course 3 starts after both finish, at
 * month 3, and finishes at month 8. Therefore, the answer is 8.
 *
 * Time Complexity: O(n + relations.size())
 * Space Complexity: O(n + relations.size())
 */

class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        vector<vector<int>> adj(n);
        for(auto &vec:relations){
            adj[vec[0]-1].push_back(vec[1]-1);
        }
        vector<int> inDeg(n,0);
        for(int i=0;i<n;i++){
            for(auto &it:adj[i]){
                inDeg[it]++;
            }
        }
        queue<int> q;
        for(int i=0;i<n;i++){
            if(inDeg[i]==0){
                q.push(i);
            }
        }
        vector<int> startTime(n,0);
        int totalMonth=0;
        while(!q.empty()){
            int u=q.front();
            q.pop();

            int finishTime=startTime[u]+time[u];
            totalMonth=max(totalMonth,finishTime);
            for(auto &neb:adj[u]){
                startTime[neb]=max(startTime[neb],finishTime);
                inDeg[neb]--;
                if(inDeg[neb]==0){
                    q.push(neb);
                }
            }
        }
        return totalMonth;
    }
};