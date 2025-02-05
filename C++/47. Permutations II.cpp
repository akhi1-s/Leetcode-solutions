#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> result; // To store all unique permutations
        vector<int> current;       // To store the current permutation
        vector<bool> visited(nums.size(), false); // Track visited elements

        // Sort the array to handle duplicates
        sort(nums.begin(), nums.end());

        // Backtracking function
        backtrack(nums, visited, current, result);
        return result;
    }

private:
    void backtrack(const vector<int>& nums, vector<bool>& visited, vector<int>& current, vector<vector<int>>& result) {
        // Base case: If the current permutation is complete, add it to the result
        if (current.size() == nums.size()) {
            result.push_back(current);
            return;
        }

        // Iterate through the array
        for (int i = 0; i < nums.size(); ++i) {
            // Skip if the element is already used
            if (visited[i]) continue;

            // Skip duplicates: If the current element is the same as the previous and the previous wasn't used
            if (i > 0 && nums[i] == nums[i - 1] && !visited[i - 1]) continue;

            // Mark the element as visited and add it to the current permutation
            visited[i] = true;
            current.push_back(nums[i]);

            // Recurse to build the next part of the permutation
            backtrack(nums, visited, current, result);

            // Backtrack: Unmark the element and remove it from the current permutation
            visited[i] = false;
            current.pop_back();
        }
    }
};
