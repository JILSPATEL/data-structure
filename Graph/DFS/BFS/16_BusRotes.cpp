class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {

        if (source == target)
            return 0;

        // stop -> buses passing through this stop
        unordered_map<int, vector<int>> stopToBuses;

        for (int busNumber = 0; busNumber < routes.size(); busNumber++) {
            for (int stop : routes[busNumber]) {
                stopToBuses[stop].push_back(busNumber);
            }
        }

        queue<pair<int, int>> bfsQueue;
        vector<bool> visitedBus(routes.size(), false);
        unordered_set<int> visitedStop;

        // Start BFS from every bus that contains source
        for (int busNumber : stopToBuses[source]) {
            bfsQueue.push({busNumber, 1});
            visitedBus[busNumber] = true;
        }

        while (!bfsQueue.empty()) {

            int currentBus = bfsQueue.front().first;
            int busesTaken = bfsQueue.front().second;
            bfsQueue.pop();

            // Visit every stop of the current bus
            for (int currentStop : routes[currentBus]) {

                if (currentStop == target)
                    return busesTaken;

                if (visitedStop.count(currentStop))
                    continue;

                visitedStop.insert(currentStop);

                // From this stop, we can switch to other buses
                for (int nextBus : stopToBuses[currentStop]) {

                    if (!visitedBus[nextBus]) {
                        visitedBus[nextBus] = true;
                        bfsQueue.push({nextBus, busesTaken + 1});
                    }
                }
            }
        }

        return -1;
    }
};