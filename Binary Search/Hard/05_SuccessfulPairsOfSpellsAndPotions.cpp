class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions,
                                long long success) {
        int n = spells.size();
        sort(potions.begin(), potions.end());
        int m = potions.size();

        vector<int> res(n);

        for (int i = 0; i < n; i++) {
            long long num = spells[i];
            int low = 0;
            int high = m - 1;
            while (low <= high) {
                int mid = (low + high) / 2;
                long long ans = num*(long long)potions[mid];
                if (ans >= success) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
            res[i]=m-low;
        }
        return res;
    }
};