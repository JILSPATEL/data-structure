# Moore’s Voting Algorithm

Moore’s Voting Algorithm is used to find majority elements in an array using
O(n) time and O(1) space.

---

## Case 1: Majority Element (> ⌊n/2⌋)

An element is a majority element if it appears more than ⌊n/2⌋ times.

### Intuition
- Each element votes for itself
- Different elements cancel each other
- A true majority element can never be fully canceled

### Algorithm
**Phase 1: Find Candidate**
- If count is 0, select current element as candidate
- Same element → increment count
- Different element → decrement count

**Phase 2: Verify Candidate**
- Count occurrences of candidate
- Check if it is > n/2

### C++ Implementation (n/2)
```cpp
int majorityElement(vector<int>& nums) {
    int count = 0, candidate = -1;

    for (int x : nums) {
        if (count == 0)
            candidate = x;
        count += (x == candidate) ? 1 : -1;
    }

    count = 0;
    for (int x : nums)
        if (x == candidate) count++;

    return (count > nums.size() / 2) ? candidate : -1;
}

# Moore’s Voting Algorithm (n/3 Majority)

This algorithm finds all elements that appear **more than ⌊n/3⌋ times** in an array.
```
---

## Key Observation
There can be **at most 2 elements** that occur more than `n/3` times.

---

## Intuition
- Maintain **two candidates** and **two counters**
- Same element increases its counter
- When three distinct elements appear, they cancel each other

---

## Algorithm

### Phase 1: Find Potential Candidates
Initialize:
- `cand1`, `cand2`
- `count1 = 0`, `count2 = 0`

Traverse the array:
1. If current element == `cand1` → `count1++`
2. Else if current element == `cand2` → `count2++`
3. Else if `count1 == 0` → `cand1 = element`, `count1 = 1`
4. Else if `count2 == 0` → `cand2 = element`, `count2 = 1`
5. Else → `count1--`, `count2--`

---

### Phase 2: Verify Candidates
- Count actual occurrences of `cand1` and `cand2`
- Include candidate if its frequency > `n/3`

---

## C++ Implementation
```cpp
vector<int> majorityElement(vector<int>& nums) {
    int cand1 = 0, cand2 = 1;
    int count1 = 0, count2 = 0;

    for (int x : nums) {
        if (x == cand1)
            count1++;
        else if (x == cand2)
            count2++;
        else if (count1 == 0) {
            cand1 = x;
            count1 = 1;
        }
        else if (count2 == 0) {
            cand2 = x;
            count2 = 1;
        }
        else {
            count1--;
            count2--;
        }
    }

    count1 = count2 = 0;
    for (int x : nums) {
        if (x == cand1) count1++;
        else if (x == cand2) count2++;
    }

    vector<int> res;
    int n = nums.size();
    if (count1 > n / 3) res.push_b_
