class Solution {
public:
    void mergeSort(vector<pair<int, int>>& arr, int left, int right,
                   vector<int>& res) {
        if (left >= right)
            return;
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, res);
        mergeSort(arr, mid + 1, right, res);
        merge(arr, left, mid, right, res);
    }

    void merge(vector<pair<int, int>>& arr, int left, int mid, int right,
               vector<int>& res) {
        vector<pair<int, int>> temp;
        int i = left, j = mid + 1;
        int rightCount = 0;

        while (i <= mid && j <= right) {
            if (arr[i].first <= arr[j].first) {
                res[arr[i].second] += rightCount;
                temp.push_back(arr[i++]);
            } else {
                rightCount++;
                temp.push_back(arr[j++]);
            }
        }
        while (i <= mid) {
            res[arr[i].second] += rightCount;
            temp.push_back(arr[i++]);
        }

        while (j <= right) {
            temp.push_back(arr[j++]);
        }

        for (int k = left; k <= right; k++) {
            arr[k] = temp[k - left];
        }
    }

    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 0);
        vector<pair<int, int>> arr;
        for (int i = 0; i < n; i++) {
            arr.push_back({nums[i], i});
        }

        mergeSort(arr, 0, n - 1, res);
        return res;
    }
};
