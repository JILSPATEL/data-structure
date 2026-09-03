/**
 * Problem: Course Schedule IV
 *
 * Description:
 * There are `numCourses` courses and prerequisite pairs [a, b], meaning
 * course `a` must be completed before course `b`. For every query [u, v],
 * determine whether `u` is a prerequisite of `v`, either directly or through
 * one or more intermediate courses.
 *
 * Intuition:
 * A prerequisite relationship is transitive. If `u` is required for `w` and
 * `w` is required for `v`, then `u` is also required for `v`. We can therefore
 * store all reachable course pairs and use the transitive closure of the
 * directed graph to answer each query in constant time.
 *
 * Approach:
 * 1. Create a boolean reachability matrix and mark every direct prerequisite.
 * 2. Use Floyd-Warshall to discover indirect prerequisite relationships.
 * 3. For each query [u, v], return whether `reachable[u][v]` is true.
 *
 * Example:
 * Input: numCourses = 4,
 *        prerequisites = [[0,1], [1,2], [2,3]],
 *        queries = [[0,3], [1,3], [3,0]]
 *
 * The chain is 0 -> 1 -> 2 -> 3, so the output is [true, true, false].
 *
 * Time Complexity: O(numCourses^3 + prerequisites.size() + queries.size())
 * Space Complexity: O(numCourses^2)
 */

class Solution {
public:
	vector<bool> checkIfPrerequisite(int numCourses,
									 vector<vector<int>>& prerequisites,
									 vector<vector<int>>& queries) {
		vector<vector<bool>> reachable(numCourses,
									   vector<bool>(numCourses, false));

		for (auto& prerequisite : prerequisites) {
			reachable[prerequisite[0]][prerequisite[1]] = true;
		}

		for (int intermediate = 0; intermediate < numCourses; intermediate++) {
			for (int course = 0; course < numCourses; course++) {
				for (int nextCourse = 0; nextCourse < numCourses; nextCourse++) {
					reachable[course][nextCourse] =
						reachable[course][nextCourse] ||
						(reachable[course][intermediate] &&
						 reachable[intermediate][nextCourse]);
				}
			}
		}

		vector<bool> answer;
		for (auto& query : queries) {
			answer.push_back(reachable[query[0]][query[1]]);
		}
		return answer;
	}
};
