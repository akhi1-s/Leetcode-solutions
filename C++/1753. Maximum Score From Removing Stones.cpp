
class Solution {
public:
    int maximumScore(int a, int b, int c) {
        vector<int> s = {a, b, c};
        sort(s.begin(), s.end());
        if (s[0] + s[1] < s[2]) return s[0] + s[1];
        return (a + b + c) >> 1;
    }
};
