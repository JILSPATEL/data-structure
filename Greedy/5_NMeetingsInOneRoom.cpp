/**
 * Problem: Maximum number of meetings in one room
 * 
 * Description:
 * Given start and end times of meetings, find the maximum number of meetings
 * that can be performed in a single meeting room such that no meetings overlap.
 * 
 * Approach:
 * 1. Greedy Strategy:
 *    - Pair meetings as (end, start) so sorting is based on end time.
 *    - Sort all meetings by their end time.
 *    - Always pick the meeting that finishes earliest.
 *    - If the next meeting starts after the last selected meeting ends,
 *      include it.
 * 
 * 2. Why Greedy Works:
 *    - Choosing the earliest finishing meeting leaves maximum room
 *      for remaining meetings.
 * 
 * Time Complexity: O(n log n) (due to sorting)
 * Space Complexity: O(n)
 */

class Solution {
public:
    int maxMeetings(vector<int>& start, vector<int>& end) {
        vector<pair<int,int>> rooms;
        int n = start.size();

        // Store meetings as (end, start)
        for(int i = 0; i < n; i++) {
            rooms.push_back({end[i], start[i]});
        }

        // Sort by end time
        sort(rooms.begin(), rooms.end());

        int cnt = 1;
        int lastMeeting = rooms[0].first;

        // Select meetings greedily
        for(int i = 1; i < n; i++) {
            if(lastMeeting < rooms[i].second) {
                cnt++;
                lastMeeting = rooms[i].first;
            }
        }

        return cnt;
    }
};
