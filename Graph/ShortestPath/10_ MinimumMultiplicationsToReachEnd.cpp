/**
 * Problem: Minimum Multiplications to Reach End
 *
 * Description:
 * Given an array of multipliers and target number,
 * find minimum operations to reach target.
 *
 * Example 1:
 * Input: arr=[2,3,4], start=1, end=8
 * Output: 2
 * Explanation: 1→2→8 or 1→3→12→... (choose 2 operations)
 *
 * Example 2:
 * Input: arr=[3,5], start=2, end=10
 * Output: -1
 * Explanation: Cannot reach 10 from 2 with multipliers [3,5]
 *
 * Example 3:
 * Input: arr=[2,4,5,6,7], start=10, end=100000
 * Output: 4
 * Explanation: Optimal multiplications to reach target
 *
 * Approach 1: BFS (Optimal)
 *
 * Observation:
 * - Every multiplication operation takes exactly 1 step
 * - Graph edges have equal weight (=1)
 * - BFS always finds shortest path when edge weights are equal
 *
 * Graph Representation:
 *
 * Node:
 *      Current number
 *
 * Edge:
 *      current → (current*num)%1000
 *
 * Steps:
 * 1. Push start node into queue
 * 2. Store minimum steps using dist[]
 * 3. Try all multipliers
 * 4. If smaller steps found:
 *      update distance
 *      push into queue
 *
 * Time Complexity:
 *      O(1000*N)
 *
 * Space Complexity:
 *      O(1000)
 */

class Solution {
public:
    int minSteps(vector<int>& arr, int start, int end) {

        if(start==end)
            return 0;

        // Queue -> {node,steps}
        queue<pair<int,int>> q;

        vector<int> dist(1000,INT_MAX);

        dist[start]=0;

        q.push({start,0});

        while(!q.empty()){

            auto curr=q.front();
            q.pop();

            int currNode=curr.first;
            int currSteps=curr.second;

            for(int &num:arr){

                int nextNode=
                (currNode*num)%1000;

                if(currSteps+1<dist[nextNode]){

                    dist[nextNode]=currSteps+1;

                    if(nextNode==end)
                        return currSteps+1;

                    q.push(
                        {nextNode,currSteps+1}
                    );
                }
            }
        }

        return -1;
    }
};

// Approach 2: Dijkstra's Algorithm (Not Optimal)

/**
 * Problem: Minimum Multiplications to Reach End
 *
 * Approach 2: Dijkstra using Priority Queue
 *
 * Observation:
 * - We can also model this as shortest path
 * - Node:
 *      Current number
 *
 * - Edge:
 *      current → (current*num)%1000
 *
 * - Weight:
 *      Every edge weight = 1
 *
 * Dijkstra Logic:
 *
 * Case 1:
 * Found smaller steps
 *
 *      dist[nextNode]=newSteps
 *
 * Case 2:
 * Ignore larger path
 *
 *      if(currSteps>dist[node])
 *          continue
 *
 * Note:
 * BFS is better because all weights are equal
 * Dijkstra works but adds extra log(V) cost
 *
 * Time Complexity:
 *      O((1000*N)log1000)
 *
 * Space Complexity:
 *      O(1000)
 */

class Solution {
public:
    int minSteps(vector<int>& arr, int start, int end) {

        if(start==end)
            return 0;

        // Min Heap -> {steps,node}
        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > pq;

        vector<int> dist(1000,INT_MAX);

        dist[start]=0;

        pq.push({0,start});

        while(!pq.empty()){

            auto curr=pq.top();
            pq.pop();

            int currSteps=curr.first;
            int currNode=curr.second;

            // Ignore outdated entries
            if(currSteps>dist[currNode])
                continue;

            for(int &num:arr){

                int nextNode=
                (currNode*num)%1000;

                int newSteps=
                currSteps+1;

                if(newSteps<dist[nextNode]){

                    dist[nextNode]=newSteps;

                    if(nextNode==end)
                        return newSteps;

                    pq.push(
                        {newSteps,nextNode}
                    );
                }
            }
        }

        return -1;
    }
};