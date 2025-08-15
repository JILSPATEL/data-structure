#include <bits/stdc++.h>
using namespace std;

vector<int> nextSmallerElements(vector<int>& nums) {
  int n = nums.size();
  vector<int> nge(n, -1);
  stack<int> st;

  for (int i = n - 1; i >= 0; i--) {
    while (!st.empty() && st.top() >= nums[i]) {
      st.pop();
    }

    if (i < n && !st.empty()) {
      nge[i] = st.top();
    }

    st.push(nums[i]);
  }

  return nge;
}

int main() {
  vector<int> v {4, 8, 5, 2, 25};
  vector<int> res = nextSmallerElements(v);
  cout << "The next greater elements are" << endl;
  for (int i = 0; i < res.size(); i++) {
    cout << res[i] << " ";
  }
  cout << endl;
}
