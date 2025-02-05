#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long kthLargestLevelSum(TreeNode* root, int k) {
        // Edge case: if the tree is empty
        if (!root) return -1;

        // Vector to store the sum of each level
        vector<long long> levelSums;

        // Queue for BFS traversal
        queue<TreeNode*> q;
        q.push(root);

        // Perform BFS to calculate level sums
        while (!q.empty()) {
            int size = q.size();
            long long levelSum = 0;

            // Process all nodes at the current level
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                levelSum += node->val;

                // Add child nodes to the queue
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            // Store the sum of the current level
            levelSums.push_back(levelSum);
        }

        // If there are fewer than k levels, return -1
        if (levelSums.size() < k) return -1;

        // Sort the level sums in descending order
        sort(levelSums.begin(), levelSums.end(), greater<long long>());

        // Return the kth largest sum
        return levelSums[k - 1];
    }
};
