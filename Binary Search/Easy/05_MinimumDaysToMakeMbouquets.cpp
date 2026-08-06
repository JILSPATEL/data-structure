/*
    PROBLEM:
    --------
    We are given:
    - bloomDay[i] : the day the i-th flower blooms
    - m : number of bouquets required
    - k : number of adjacent flowers needed per bouquet

    We must return the minimum number of days required to make
    exactly m bouquets using k adjacent flowers.

    If it is not possible, return -1.


    APPROACH USED:
    --------------
    We use Binary Search on Answer.

    Why?
    Because if it is possible to make m bouquets on day D,
    then it will also be possible on any day greater than D.
    This makes the solution monotonic, so Binary Search works.


    STEPS:
    ------
    1. First check:
       If m * k > total flowers,
       then it is impossible -> return -1.

    2. Define search space:
       low  = minimum bloom day
       high = maximum bloom day

    3. Apply Binary Search:
       For each mid (candidate day),
       check if we can make m bouquets by that day.

    4. To check feasibility:
       - Traverse the array
       - Count consecutive flowers with bloomDay <= mid
       - For every k consecutive flowers, form 1 bouquet
       - If total bouquets >= m -> possible


    TIME COMPLEXITY:
    ----------------
    solve() takes O(n)
    Binary Search runs O(log(maxDay))

    Overall Complexity:
    O(n log(maxDay))

    SPACE COMPLEXITY:
    -----------------
    O(1)  (no extra space used)


    KEY IDEA:
    ---------
    Binary Search on minimum valid day
    + Greedy counting of consecutive flowers
*/


class Solution {
public:

    bool solve(vector<int> &arr, int m, int k, int mid) {
        int cnt = 0;
        int bouquet = 0;

        for(int i = 0; i < arr.size(); i++) {
            if(arr[i] <= mid) {
                cnt++;
            }
            else {
                bouquet += cnt / k;
                cnt = 0;
            }
        }

        bouquet += cnt / k;

        return bouquet >= m;
    }

    int minDays(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size();

        if ((long long)m * k > n) 
            return -1;

        int low = *min_element(bloomDay.begin(), bloomDay.end());
        int high = *max_element(bloomDay.begin(), bloomDay.end());

        while(low <= high) {
            int mid = (low + high) / 2;

            if(solve(bloomDay, m, k, mid)) {
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }

        return low;
    }
};
