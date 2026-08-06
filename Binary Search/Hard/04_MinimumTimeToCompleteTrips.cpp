/*
Problem Description:
Given an array time where time[i] is the time taken by the i-th bus to make one trip,
and an integer totalTrips, find the minimum time required for all buses combined to make
at least totalTrips trips.

Intuition:
Each bus can make floor(t / time[i]) trips in t units of time. The total number of trips
made by all buses is therefore the sum of these values. We need the smallest t such that
this sum is at least totalTrips.

We can binary search on the answer t because the number of trips is non-decreasing as t increases.
- low starts at 1 (minimum possible time).
- high can be min(time) * totalTrips, because the fastest bus alone can complete all trips in that time.
- For each candidate mid, compute the total trips made by all buses in mid time.
- If the total trips >= totalTrips, the answer may be mid or smaller, so move left.
- Otherwise, move right.

Example:
Input: time = [1, 2, 3], totalTrips = 5
Check t = 3: bus1 -> 3 trips, bus2 -> 1 trip, bus3 -> 1 trip, total = 5. So 3 is valid.
Check lower values: t = 2 gives 2 + 1 + 0 = 3 trips, not enough.
Thus the minimum time is 3.
*/

class Solution {
public:
    typedef long long ll;

    ll solve(vector<int> &time, ll mid) {
        ll trips = 0;

        for (int t : time) {
            trips += mid / t; 
        }

        return trips;
    }

    long long minimumTime(vector<int>& time, int totalTrips) {
        ll low = 1;
        ll high = 1LL * (*min_element(time.begin(), time.end())) * totalTrips;

        while (low <= high) {
            ll mid = low + (high - low) / 2;

            if (solve(time, mid) >= totalTrips) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return low;
    }
};