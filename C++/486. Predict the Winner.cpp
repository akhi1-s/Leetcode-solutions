#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        
        // Create a DP table initialized to 0
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // Base case: single elements
        for (int i = 0; i < n; ++i) {
            dp[i][i] = nums[i];
        }
        
        // Fill the DP table for subarrays of increasing lengths
        for (int length = 2; length <= n; ++length) {  // length of the subarray
            for (int left = 0; left <= n - length; ++left) {
                int right = left + length - 1;
                
                // Recurrence relation
                dp[left][right] = max(nums[left] - dp[left + 1][right],
                                      nums[right] - dp[left][right - 1]);
            }
        }
        
        // Player 1 wins if their score difference is non-negative
        return dp[0][n - 1] >= 0;
    }
};
