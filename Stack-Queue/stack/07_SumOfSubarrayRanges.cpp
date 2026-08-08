class Solution {
public:
    vector<int> findNGE(vector<int>& nums) {
        int n = nums.size();
        vector<int> nge(n, n);
        stack<int> st;
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.top()] <= nums[i]) st.pop();
            if (!st.empty()) nge[i] = st.top();
            st.push(i);
        }
        return nge;
    }

    vector<int> findPGE(vector<int>& nums) {
        int n = nums.size();
        vector<int> pge(n, -1);
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[st.top()] < nums[i]) st.pop();
            if (!st.empty()) pge[i] = st.top();
            st.push(i);
        }
        return pge;
    }

    vector<int> findNSE(vector<int>& nums) {
        int n = nums.size();
        vector<int> nse(n, n);
        stack<int> st;
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.top()] >= nums[i]) st.pop();
            if (!st.empty()) nse[i] = st.top();
            st.push(i);
        }
        return nse;
    }

    vector<int> findPSE(vector<int>& nums) {
        int n = nums.size();
        vector<int> pse(n, -1);
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[st.top()] > nums[i]) st.pop();
            if (!st.empty()) pse[i] = st.top();
            st.push(i);
        }
        return pse;
    }

    long long sumOfMax(vector<int>& arr) {
        vector<int> nge = findNGE(arr);
        vector<int> pge = findPGE(arr);
        long long total = 0;
        for (int i = 0; i < arr.size(); i++) {
            long long left = i - pge[i];
            long long right = nge[i] - i;
            total += 1LL * arr[i] * left * right;
        }
        return total;
    }

    long long sumOfMin(vector<int>& arr) {
        vector<int> nse = findNSE(arr);
        vector<int> pse = findPSE(arr);
        long long total = 0;
        for (int i = 0; i < arr.size(); i++) {
            long long left = i - pse[i];
            long long right = nse[i] - i;
            total += 1LL * arr[i] * left * right;
        }
        return total;
    }

    long long subArrayRanges(vector<int>& nums) {
        return sumOfMax(nums) - sumOfMin(nums);
    }
};