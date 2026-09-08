/*
Problem Description:
Given three integers a, b, and c, find the minimum number of bit flips needed in a or b
so that (a OR b) becomes equal to c. Flipping one bit changes only one bit in either a
or b.

Intuition:
Each bit position is independent. If the corresponding bit of c is 1, at least one of
the bits in a or b must be 1; a flip is needed only when both are 0. If the bit of c is
0, both bits in a and b must be 0, so every 1 among them must be flipped off.

Approach:
1. Inspect each bit position from 0 through 30.
2. Extract the bits of a, b, and c at that position.
3. For c = 1, add one flip when both a and b are 0.
4. For c = 0, add the number of 1 bits in a and b.
5. Return the total number of required flips.

Example:
a = 2 (010), b = 3 (011), c = 1 (001)
At bit 0, a OR b is already 1, so no flip is needed. At bit 1, c is 0 but both a and
b contain 1, so both bits must be flipped. The minimum number of flips is 2.

Time Complexity: O(31), or O(1) for fixed-width integers
Space Complexity: O(1)
*/

class Solution {
public:
    int minFlips(int a, int b, int c) {
        int cnt = 0;

        for (int i = 0; i < 31; i++) {
            int aBit = (a >> i) & 1;
            int bBit = (b >> i) & 1;
            int cBit = (c >> i) & 1;

            if (cBit == 1) {
                if (aBit == 0 && bBit == 0)
                    cnt++;
            } 
            else {
                cnt += aBit + bBit;
            }
        }

        return cnt;
    }
};
