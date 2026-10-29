/*
Problem: Find the Best BVH Split Using Surface Area Heuristic (SAH)

You are given N 3D bounding boxes already sorted by their x-coordinate
centroid. Your task is to split them into two non-empty groups such that
the Surface Area Heuristic (SAH) cost is minimized.

For every possible split k:
    Left group  = first k boxes (indices 0 to k-1)
    Right group = remaining N-k boxes (indices k to N-1)

The SAH cost is calculated as:

    Cost(k) = Ctrav
            + (SA_left / SA_parent) * k * Cisect
            + (SA_right / SA_parent) * (N-k) * Cisect

Where:
    Ctrav     = Cost of traversing a BVH node
    Cisect    = Cost of intersecting a ray with one object
    SA_left   = Surface area of the left group's bounding box
    SA_right  = Surface area of the right group's bounding box
    SA_parent = Surface area of the bounding box containing all objects

The surface area of a 3D bounding box is:

    SA = 2 * (dx*dy + dy*dz + dz*dx)

Approach:
1. Build a prefix array where prefix[i] stores the bounding box
   enclosing objects from index 0 to i.
2. Build a suffix array where suffix[i] stores the bounding box
   enclosing objects from index i to N-1.
3. Evaluate every valid split k from 1 to N-1 using prefix[k-1]
   for the left group and suffix[k] for the right group.
4. Calculate the SAH cost for each split and select the split
   with the minimum cost.

The boxes are already sorted, so do not sort them again.

Time Complexity: O(N)
Space Complexity: O(N)
*/

#include <bits/stdc++.h>
using namespace std;

struct Box {
    double xmin, ymin, zmin;
    double xmax, ymax, zmax;
};

double surfaceArea(const Box& b) {
    double dx = b.xmax - b.xmin;
    double dy = b.ymax - b.ymin;
    double dz = b.zmax - b.zmin;

    return 2.0 * (dx * dy + dy * dz + dz * dx);
}

Box mergeBoxes(const Box& a, const Box& b) {
    return {
        min(a.xmin, b.xmin),
        min(a.ymin, b.ymin),
        min(a.zmin, b.zmin),
        max(a.xmax, b.xmax),
        max(a.ymax, b.ymax),
        max(a.zmax, b.zmax)
    };
}

int main() {
    int N;
    cin >> N;

    vector<Box> boxes(N);

    for (int i = 0; i < N; i++) {
        cin >> boxes[i].xmin >> boxes[i].ymin >> boxes[i].zmin
            >> boxes[i].xmax >> boxes[i].ymax >> boxes[i].zmax;
    }

    double Ctrav, Cisect;
    cin >> Ctrav >> Cisect;

    if (N < 2) {
        cout << "No valid split possible\n";
        return 0;
    }

    vector<Box> prefix(N), suffix(N);

    prefix[0] = boxes[0];

    for (int i = 1; i < N; i++) {
        prefix[i] = mergeBoxes(prefix[i - 1], boxes[i]);
    }

    suffix[N - 1] = boxes[N - 1];

    for (int i = N - 2; i >= 0; i--) {
        suffix[i] = mergeBoxes(boxes[i], suffix[i + 1]);
    }

    double SA_parent = surfaceArea(prefix[N - 1]);

    if (SA_parent == 0.0) {
        cout << "Parent bounding box has zero surface area\n";
        return 0;
    }

    double minCost = numeric_limits<double>::max();
    int bestSplit = -1;

    for (int k = 1; k < N; k++) {
        double SA_left = surfaceArea(prefix[k - 1]);
        double SA_right = surfaceArea(suffix[k]);

        double cost = Ctrav
                    + (SA_left / SA_parent) * k * Cisect
                    + (SA_right / SA_parent) * (N - k) * Cisect;

        if (cost < minCost) {
            minCost = cost;
            bestSplit = k;
        }
    }

    cout << fixed << setprecision(6);
    cout << "Best split k: " << bestSplit << '\n';
    cout << "Minimum SAH cost: " << minCost << '\n';

    return 0;
}