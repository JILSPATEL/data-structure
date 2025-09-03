class MKAverage {
    int m,k;
    queue<int>q;
    vector<int> arr;
public:
    MKAverage(int m, int k) {
        this->m=m;
        this->k=k;
    }
    
    void addElement(int num) {
        q.push(num);
        arr.insert(lower_bound(arr.begin(), arr.end(), num), num);
        if(q.size()>m){
            int old=q.front();
            q.pop();
            arr.erase(lower_bound(arr.begin(), arr.end(), old));
        }
    }
    
    int calculateMKAverage() {
        if (q.size() < m) return -1;
        long long sum = 0;
        for (int i = k; i < m - k; i++) sum += arr[i];
        return sum / (m - 2*k);
    }
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */
