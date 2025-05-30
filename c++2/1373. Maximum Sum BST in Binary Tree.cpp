class Solution {
public:
    int maxSumBST(TreeNode* root) {
        using RET = tuple<bool, int, int, int>;
        int result = 0;
        RET ret;
        vector<tuple<TreeNode*, shared_ptr<vector<RET>>, RET *>> stk = {{root, nullptr, &ret}};
        while (!stk.empty()) {
            const auto [node, tmp, ret] = stk.back(); stk.pop_back();
            if (tmp) {
                const auto& [lvalid, lsum, lmin, lmax] = (*tmp)[0];
                const auto& [rvalid, rsum, rmin, rmax] = (*tmp)[1];
                if (lvalid && rvalid && lmax < node->val && node->val < rmin) {
                    const auto& total = lsum + node->val + rsum;
                    result = max(result, total);
                    *ret = {true, total, min(lmin, node->val), max(node->val, rmax)};
                    continue;
                }
                *ret = {false, 0, 0, 0};
                continue;
            }
            if (!node) {
                *ret = {true, 0,
                        numeric_limits<int>::max(),
                        numeric_limits<int>::min()};
                continue;
            }
            const auto& new_tmp = make_shared<vector<RET>>(2);
            stk.emplace_back(node, new_tmp, ret);
            stk.emplace_back(node->right, nullptr, &((*new_tmp)[1]));
            stk.emplace_back(node->left, nullptr, &((*new_tmp)[0]));
        }
        return result;
    }
};
