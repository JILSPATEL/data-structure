/**
 * Problem: Divide Cards into Groups of Consecutive Numbers
 * 
 * Description:
 * - Given an array of cards, divide them into groups of size `groupSize`
 * - Each group must contain consecutive numbers
 * 
 * Approach 1 (Greedy + Ordered Map) ✅ BEST:
 * - Count frequency using map (sorted keys)
 * - Always start from the smallest available card
 * - Try forming a group of size `groupSize`
 * - Reduce frequency for consecutive elements
 * 
 * Time Complexity: O(N log N)
 * Space Complexity: O(N)
 */

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        if(hand.size() % groupSize != 0) return false;

        map<int,int> freq;

        // Count frequency
        for(int card : hand) {
            freq[card]++;
        }

        // Process in sorted order
        for(auto &[card, cnt] : freq) {
            while(freq[card] > 0) {

                // Try forming group
                for(int i = 0; i < groupSize; i++) {
                    int nextCard = card + i;

                    if(freq.find(nextCard) == freq.end() || freq[nextCard] == 0) {
                        return false;
                    }

                    freq[nextCard]--;
                }
            }
        }

        return true;
    }
};


/**
 * Problem: Divide Cards into Groups of Consecutive Numbers
 * 
 * Approach 2 (Min Heap + Frequency Map):
 * - Count frequency using unordered_map
 * - Push all unique cards into min heap
 * - Always pick smallest card
 * - Form group of size `groupSize`
 * - Decrease frequency and clean heap when freq becomes 0
 * 
 * Time Complexity: O(N log N)
 * Space Complexity: O(N)
 * 
 * Note:
 * - More complex than map approach
 * - Requires careful heap cleanup
 */

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        if(hand.size() % groupSize != 0) return false;

        unordered_map<int,int> freq;

        // Count frequency
        for(int card : hand) {
            freq[card]++;
        }

        // Min heap of unique elements
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for(auto &p : freq) {
            minHeap.push(p.first);
        }

        while(!minHeap.empty()) {
            int start = minHeap.top();

            // Try forming group
            for(int i = 0; i < groupSize; i++) {
                int card = start + i;

                if(freq[card] == 0) return false;

                freq[card]--;

                // If frequency becomes zero, it should match heap top
                if(freq[card] == 0) {
                    if(card != minHeap.top()) return false;
                    minHeap.pop();
                }
            }
        }

        return true;
    }
};