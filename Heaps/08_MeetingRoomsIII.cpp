/*
================================================================================
                    PROBLEM: Meeting Rooms III
================================================================================

DESCRIPTION:
-----------
You are given an integer 'n' representing the number of meeting rooms (numbered 
0 to n-1) and a 2D array 'meetings' where meetings[i] = [start_i, end_i] 
represents a meeting that needs to be scheduled.

Your task is to find which room is used the most (i.e., has the most meetings 
scheduled in it). If there's a tie, return the room with the smallest number.

Key Points:
- Meetings must be assigned to rooms as they arrive in chronological order
- If a room is free when a meeting starts, use that room
- If no room is free, assign the meeting to the room that will be free earliest
- If there's still a tie, use the room with the smallest number
- The meeting will be scheduled from start_i to (end_time + duration) if delayed

================================================================================
APPROACH (Greedy + Min Heaps):
===============================
1. Sort meetings by start time (to process chronologically)
2. Maintain two min-heaps:
   - 'available': min-heap of available room IDs (sorted by room number)
   - 'busy': min-heap of (finish_time, room_id) for rooms currently in use
3. Track meeting count for each room using a count array
4. For each meeting in order:
   a) Free up all rooms whose meetings ended before/at the current start time
   b) If any room is available, assign to the one with smallest ID
   c) If no room is available, assign to the room freeing up earliest (with smallest ID as tiebreaker)
   d) Increment the count for that room
5. Return the room with maximum count (smallest ID if tie)

TIME COMPLEXITY: O(m * log n) where m = number of meetings, n = number of rooms
SPACE COMPLEXITY: O(n) for heaps and count array

================================================================================
INTUITION:
==========
Think of this as a scheduling problem where we process meetings in order.
- Sort meetings first so we handle them chronologically (natural flow)
- Use heaps to efficiently find:
  * The smallest available room (min-heap of room IDs)
  * The room that becomes free earliest (min-heap of end times)
- Greedy choice: Always pick the smallest available room or the one freeing up 
  earliest (with smallest ID as tiebreaker)
- This ensures fair scheduling and maximum room utilization

The key insight is that if rooms are full, we don't "wait" - we schedule the
meeting to start as soon as some room becomes free, but the meeting duration
remains the same. This might cause cascading delays.

================================================================================
EXAMPLE:
========
Input: n = 3, meetings = [[0,10], [1,5], [1,6], [1,7]]

Step 1: Sort meetings (already sorted): [[0,10], [1,5], [1,6], [1,7]]
        Initialize: available = {0, 1, 2}, busy = {}, cnt = [0, 0, 0]

Step 2: Process meeting [0, 10]:
        - No rooms to free (busy is empty)
        - Room 0 is available, assign to room 0
        - cnt = [1, 0, 0], busy = {(10, 0)}

Step 3: Process meeting [1, 5]:
        - Check busy rooms: room 0 finishes at 10 > 1, so not free yet
        - Room 1 is available, assign to room 1
        - cnt = [1, 1, 0], busy = {(10, 0), (5, 1)}

Step 4: Process meeting [1, 6]:
        - Check busy rooms: room 1 finishes at 5 >= 1, but needs to check order
        - No rooms free yet
        - Room 2 is available, assign to room 2
        - cnt = [1, 1, 1], busy = {(5, 1), (10, 0), (6, 2)}

Step 5: Process meeting [1, 7]:
        - Check busy rooms: room 1 finishes at 5 >= 1? No (we want <=1)
        - No available rooms
        - Room 1 will be free earliest at time 5
        - Duration of meeting = 7 - 1 = 6
        - New end time = 5 + 6 = 11
        - cnt = [1, 2, 1], busy = {(6, 2), (10, 0), (11, 1)}

Step 6: Count results: cnt = [1, 2, 1]
        Room 1 has most bookings (2)
        Return: 1

================================================================================
*/

class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        sort(meetings.begin(), meetings.end());
        priority_queue<int, vector<int>, greater<int>> available;
        priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                       greater<pair<long long, int>>>
            busy;
        vector<int> cnt(n,0);
        for(int i=0;i<n;i++){
            available.push(i);
        }
        for(auto &meeting:meetings){
            long long start=meeting[0];
            long long end=meeting[1];
            long long duration=end-start;
            //Free Room Whose Meetings Are Completed
            while(!busy.empty() && busy.top().first<=start){
                int room=busy.top().second;
                busy.pop();
                available.push(room);
            }
            //Smallest Available Room
            if(!available.empty()){
                int room=available.top();
                available.pop();
                cnt[room]++;
                busy.push({end,room});
            }
            //No Room Available
            else{
                auto [freeTime,room]=busy.top();
                busy.pop();
                long long newEnd=freeTime+duration;
                cnt[room]++;
                busy.push({newEnd,room});
            }
        }
        int ans=0;
        for(int i=1;i<n;i++){
            if(cnt[i]>cnt[ans]){
                ans=i;
            }
        }
        return ans;
    }
};