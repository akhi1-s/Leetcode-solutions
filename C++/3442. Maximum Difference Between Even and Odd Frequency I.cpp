class Solution {
public:
    int maxDifference(string s) {
        int counts[26] = {0};
        for (char c : s) {
            counts[c - 'a']++;
        }
        
        int max_odd = 0;
        int min_even = INT_MAX;
        
        for (int i = 0; i < 26; ++i) {
            int cnt = counts[i];
            if (cnt == 0) continue;
            if (cnt % 2 == 0) {
                if (cnt < min_even) {
                    min_even = cnt;
                }
            } else {
                if (cnt > max_odd) {
                    max_odd = cnt;
                }
            }
        }
        
        return max_odd - min_even;
    }
};
