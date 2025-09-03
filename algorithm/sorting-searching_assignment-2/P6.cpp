class Solution {
public:
    bool check(vector<int>& arr, int mid, int m, int k) {
        int n = arr.size();
        int cnt = 0;    
        int roseB = 0;   

        for (int i = 0; i < n; i++) {
            if (arr[i] <= mid) {
                cnt++;
            } else {
                roseB += cnt / k;
                cnt = 0;
            }
        }
        roseB += cnt / k; 
        return roseB >= m;
    }

    int minDays(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size();
        if ((long long)m * k > n) 
            return -1;

        int low = *min_element(bloomDay.begin(), bloomDay.end());
        int high = *max_element(bloomDay.begin(), bloomDay.end());
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(bloomDay, mid, m, k)) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }
};

