class Solution {
public:
    string removeDuplicateLetters(string s) {
        int n = s.size();
        vector<int> lastPos(26, 0);
        for (int i = 0; i < n; i++) {
            lastPos[s[i] - 'a'] = i;
        }
        string st;
        vector<bool> visited(26, false);

        for(int i=0;i<n;i++){
            char c=s[i];

            if(visited[c-'a']){
                continue;
            }
            while(!st.empty() && st.back()>c && lastPos[st.back()-'a']>i){
                visited[st.back()-'a']=false;
                st.pop_back();
            }
            st.push_back(c);
            visited[c-'a']=true;
        }
        return st;
    }
};