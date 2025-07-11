
class Solution {
public:
    double minAreaFreeRect(vector<vector<int>>& points) {
        auto f = [](int x, int y) {
            return x * 40001 + y;
        };
        int n = points.size();
        unordered_set<int> s;
        for (auto& p : points) {
            s.insert(f(p[0], p[1]));
        }
        double ans = 1e20;
        for (int i = 0; i < n; ++i) {
            int x1 = points[i][0], y1 = points[i][1];
            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    int x2 = points[j][0], y2 = points[j][1];
                    for (int k = j + 1; k < n; ++k) {
                        if (k != i) {
                            int x3 = points[k][0], y3 = points[k][1];
                            int x4 = x2 - x1 + x3, y4 = y2 - y1 + y3;
                            if (x4 >= 0 && x4 < 40000 && y4 >= 0 && y4 <= 40000 && s.count(f(x4, y4))) {
                                if ((x2 - x1) * (x3 - x1) + (y2 - y1) * (y3 - y1) == 0) {
                                    int ww = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
                                    int hh = (x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1);
                                    ans = min(ans, sqrt(1LL * ww * hh));
                                }
                            }
                        }
                    }
                }
            }
        }
        return ans == 1e20 ? 0 : ans;
    }
};
