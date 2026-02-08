class Solution {
public:
    string removeKdigits(string num, int k) {
        stack<char> st;
        string newNum = "";
        int n = num.size();
        for (char ch : num) {
            while (!st.empty() && st.top() > ch && k > 0) {
                st.pop();
                k--;
            }
            st.push(ch);
        }
        while (k > 0 && !st.empty()) {
            st.pop();
            k--;
        }
        while (!st.empty()) {
            newNum += st.top();
            st.pop();
        }
        reverse(newNum.begin(), newNum.end());
        int i = 0;
        while (i < newNum.size() && newNum[i] == '0') {
            i++;
        }
        // string ans = "";
        // for (int j = i; j < newNum.size(); j++) {
        //     ans.push_back(newNum[j]);
        // }
        // string ans=newNum.substr(i,newNum.size());
        // if (!ans.size()) {
        //     ans += '0';
        // }
        string ans = (i < newNum.size()) ? newNum.substr(i) : "0";
        return ans;
    }
};