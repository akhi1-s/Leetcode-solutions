
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class FindElements {
public:
    FindElements(TreeNode* root) {
        root->val = 0;
        dfs(root);
    }

    bool find(int target) {
        return s.contains(target);
    }

private:
    unordered_set<int> s;

    void dfs(TreeNode* root) {
        s.insert(root->val);
        if (root->left) {
            root->left->val = root->val * 2 + 1;
            dfs(root->left);
        }
        if (root->right) {
            root->right->val = root->val * 2 + 2;
            dfs(root->right);
        }
    };
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */
