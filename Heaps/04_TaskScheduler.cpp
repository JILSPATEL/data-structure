/**
 * Problem: Task Scheduler (Leetcode 621)
 *
 * Goal:
 * Find the minimum time required to execute all tasks with a cooldown `n`
 * such that same tasks have at least `n` units gap.
 *
 * ------------------------------------------------------
 * 🔹 Approach: Max Heap + Greedy Simulation
 * ------------------------------------------------------
 * 1. Count frequency of each task.
 * 2. Push all frequencies into a max heap.
 * 3. Process tasks in cycles of (n + 1):
 *      - In one cycle, we can execute at most (n+1) different tasks.
 *      - Always pick the most frequent tasks first.
 * 4. Reduce frequency and store remaining tasks temporarily.
 * 5. Push remaining tasks back into heap.
 * 6. If heap becomes empty → only count actual tasks done.
 *    Else → we must count full cycle (including idle slots).
 *
 * ------------------------------------------------------
 * 🔹 Key Idea:
 * We try to fill each block of size (n+1) with distinct tasks.
 * If not enough tasks → idle slots are added automatically.
 *
 * ------------------------------------------------------
 * 🔹 Time Complexity:
 * O(T log 26) ≈ O(T)
 *
 * 🔹 Space Complexity:
 * O(26) ≈ O(1)
 */
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {

        // Step 1: Count frequency
        vector<int> freq(26, 0);
        for (char ch : tasks) {
            freq[ch - 'A']++;
        }

        // Step 2: Max Heap
        priority_queue<int> pq;
        for (int f : freq) {
            if (f > 0) pq.push(f);
        }

        int time = 0;

        // Step 3: Process until heap empty
        while (!pq.empty()) {
            vector<int> temp;

            // Step 4: One cycle of size (n+1)
            for (int i = 0; i <= n; i++) {
                if (!pq.empty()) {
                    int f = pq.top();
                    pq.pop();
                    f--;
                    temp.push_back(f);
                }
            }

            // Step 5: Push remaining back
            for (int f : temp) {
                if (f > 0) pq.push(f);
            }

            // Step 6: Update time
            if (pq.empty()) {
                time += temp.size();   // no idle needed
            } else {
                time += (n + 1);       // full cycle (with idle)
            }
        }

        return time;
    }
};