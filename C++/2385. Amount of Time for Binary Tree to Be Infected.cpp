#include <unordered_map>
#include <queue>
using namespace std;

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
class Solution {
public:
    // Helper function to build the parent map and find the start node
    TreeNode* buildParentMap(TreeNode* root, unordered_map<TreeNode*, TreeNode*>& parentMap, int start) {
        queue<TreeNode*> q;
        q.push(root);
        TreeNode* startNode = nullptr;
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            if (node->val == start) {
                startNode = node;
            }
            
            if (node->left) {
                parentMap[node->left] = node;
                q.push(node->left);
            }
            if (node->right) {
                parentMap[node->right] = node;
                q.push(node->right);
            }
        }
        return startNode;
    }

    int amountOfTime(TreeNode* root, int start) {
        // Step 1: Build the parent map and find the start node
        unordered_map<TreeNode*, TreeNode*> parentMap; // Maps child -> parent
        TreeNode* startNode = buildParentMap(root, parentMap, start);
        
        // Step 2: Perform BFS to simulate the spread of infection
        queue<TreeNode*> q;
        unordered_map<TreeNode*, bool> visited;
        q.push(startNode);
        visited[startNode] = true;
        
        int minutes = 0;
        
        while (!q.empty()) {
            int size = q.size();
            bool spreadOccurred = false;
            
            for (int i = 0; i < size; ++i) {
                TreeNode* node = q.front();
                q.pop();
                
                // Check the left child
                if (node->left && !visited[node->left]) {
                    q.push(node->left);
                    visited[node->left] = true;
                    spreadOccurred = true;
                }
                
                // Check the right child
                if (node->right && !visited[node->right]) {
                    q.push(node->right);
                    visited[node->right] = true;
                    spreadOccurred = true;
                }
                
                // Check the parent
                if (parentMap.find(node) != parentMap.end() && !visited[parentMap[node]]) {
                    q.push(parentMap[node]);
                    visited[parentMap[node]] = true;
                    spreadOccurred = true;
                }
            }
            
            // If any spread occurred in this minute, increment the timer
            if (spreadOccurred) {
                minutes++;
            }
        }
        
        return minutes;
    }
};
