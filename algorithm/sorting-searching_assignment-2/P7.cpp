class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        sort(timePoints.begin(), timePoints.end());
        int n = timePoints.size();
        vector<int> minutes;

        // Convert all times to minutes
        for (auto &s : timePoints) {
            int h = stoi(s.substr(0, 2));
            int m = stoi(s.substr(3, 2));
            minutes.push_back(h * 60 + m);
        }

        int minDiff = INT_MAX;
        for (int i = 0; i < n - 1; i++) {
            minDiff = min(minDiff, minutes[i + 1] - minutes[i]);
        }
         minDiff = min(minDiff, 1440 - (minutes.back() - minutes.front()));
         return minDiff;
    }
};
