
class Solution {
public:
    bool check(vector<int>& nums) {
        int n = nums.size();
        int countViolations = 0;

        // Traverse the array to count order violations
        for (int i = 0; i < n; ++i) {
            // Compare current element with the next element (circularly)
            if (nums[i] > nums[(i + 1) % n]) {
                countViolations++;
            }
            // If more than one violation is found, return false
            if (countViolations > 1) {
                return false;
            }
        }

        // If we have at most one violation, the array is sorted and rotated
        return true;
    }
};
