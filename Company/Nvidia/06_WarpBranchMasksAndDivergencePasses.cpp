/*
1. Understand the Problem

A GPU warp contains 32 threads numbered from 0 to 31.

Each thread evaluates a condition:
- 1: The thread follows branch A.
- 0: The thread follows branch B.

We need to calculate three things:
1. A 32-bit mask representing threads that follow branch A.
2. A 32-bit mask representing threads that follow branch B.
3. The number of execution passes required.

Both masks must be printed in uppercase hexadecimal
with exactly eight digits.


2. What Is a Bit Mask?

A bit mask is an integer in which each bit represents a thread.

Bit i corresponds to thread i.

For a simplified example with four threads:

Thread:      T3 T2 T1 T0
Condition:    1  0  1  0

Mask A = 1010
Mask B = 0101

In the actual problem, we use 32 bits instead of four.

Each bit is set to 1 if its corresponding thread follows
that branch; otherwise, it remains 0.


3. How Do We Set a Bit?

For thread i, create a number with only bit i set:

    uint32_t bit = (uint32_t(1) << i);

Use the bitwise OR operator (|=) to set that bit in
the appropriate mask:

    if (conditions[i] == 1)
        maskA |= bit;
    else
        maskB |= bit;

The OR operator preserves previously set bits while
adding the current thread's bit.

For example, if threads 0 and 2 follow branch A:

    Binary mask = 00000000 00000000 00000000 00000101

Bits 0 and 2 are set, representing those two threads.


4. How Do We Calculate Execution Passes?

The main concept is warp divergence.

If all threads follow the same branch, only one branch
needs to execute.

If some threads follow branch A and others follow branch B,
both branches must execute in separate passes under the
simplified execution model used by this problem.

Cases:

- Mask A is nonzero and mask B is zero:
  Passes = 1

- Mask A is zero and mask B is nonzero:
  Passes = 1

- Both masks are nonzero:
  Passes = 2

The formula is:

    int passes = (maskA != 0 && maskB != 0) ? 2 : 1;

Example:
If all 32 conditions are 1:

    Mask A = 0xFFFFFFFF
    Mask B = 0x00000000
    Passes = 1

We use an unsigned 32-bit integer because thread 31
corresponds to the highest bit.


5. Output Formatting

The masks must be printed as uppercase hexadecimal
with exactly eight digits.

For example:

    00000005 0000000A 2

Use the appropriate output formatting, such as:

    printf("%08X %08X %d\n", maskA, maskB, passes);

The %08X format prints an unsigned integer in uppercase
hexadecimal, padding it with leading zeros to eight digits.


6. Complexity Analysis

Time Complexity: O(32) = O(1)
We process exactly 32 thread conditions.

Space Complexity: O(1)
We use two masks and a fixed number of variables.


Interview Recognition:
Whenever a problem represents threads, flags, or states
using individual bits, consider bit masks and bitwise
operations.
*/

#include <bits/stdc++.h>
using namespace std;

string warpBranchMasks(const vector<int>& conditions) {
    unsigned int maskA = 0, maskB = 0;

    for (int i = 0; i < 32; i++) {
        if (conditions[i] == 1)
            maskA |= (1U << i);
        else
            maskB |= (1U << i);
    }

    int passes = (maskA != 0 && maskB != 0) ? 2 : 1;

    stringstream ss;
    ss << "0x" << uppercase << hex
       << setw(8) << setfill('0') << maskA << " ";

    ss << "0x" << uppercase << hex
       << setw(8) << setfill('0') << maskB << "\n";

    ss << dec << passes;

    return ss.str();
}

int main() {
    vector<int> conditions(32);

    for (int i = 0; i < 32; i++)
        cin >> conditions[i];

    cout << warpBranchMasks(conditions) << endl;

    return 0;
}