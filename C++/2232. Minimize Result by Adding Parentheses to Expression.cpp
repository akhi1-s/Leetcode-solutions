#include <string>
#include <climits>
#include <vector>

class Solution {
public:
    // Function to convert a vector of char digits to an integer, or return 1 if the vector is empty
    int GetNum(const std::vector<char>& digits) {
        if (digits.empty()) {
            return 1;
        }
        return std::stoi(std::string(digits.begin(), digits.end()));
    }

    // Function to find the optimal insertion of parentheses in an addition expression to minimize result
    std::string minimizeResult(const std::string& expression) {
        // Find the position of the plus sign
        size_t plusPosition = expression.find('+');
        // Split the expression into two parts based on the plus sign
        std::string leftPart = expression.substr(0, plusPosition);
        std::string rightPart = expression.substr(plusPosition + 1);

        // Initialize minimum sum to a very large number
        int minimumSum = INT_MAX;
        // String to hold the answer
        std::string answer;

        // Vectors to hold the digits of the current partition
        std::vector<char> prefixArray, currentLeftArray(leftPart.begin(), leftPart.end()),
                          currentRightArray(rightPart.begin(), rightPart.end()), suffixArray;

        // Iterate through the left part of the equation character by character
        for (size_t i = 0; i <= leftPart.size(); ++i) {
            // Reset the current right array and suffix array for each iteration of the left array
            currentRightArray.assign(rightPart.begin(), rightPart.end());
            suffixArray.clear();

            // Iterate through the right part of the equation character by character
            for (size_t j = 0; j <= rightPart.size(); ++j) {
                // Calculate the current value with the parentheses inserted
                int currentValue = (GetNum(currentLeftArray) + GetNum(currentRightArray)) *
                                   GetNum(prefixArray) * GetNum(suffixArray);

                // If the current value is less than the minimum sum found so far
                if (currentValue < minimumSum) {
                    // Update the minimum sum and the answer string
                    minimumSum = currentValue;
                    answer = std::string(prefixArray.begin(), prefixArray.end()) +
                             "(" + std::string(currentLeftArray.begin(), currentLeftArray.end()) +
                             "+" + std::string(currentRightArray.begin(), currentRightArray.end()) +
                             ")" + std::string(suffixArray.begin(), suffixArray.end());
                }

                // If there are still characters in the right array, relocate the last one to the suffix array
                if (!currentRightArray.empty()) {
                    suffixArray.insert(suffixArray.begin(), currentRightArray.back());
                    currentRightArray.pop_back();
                }
            }

            // If there are still characters in the left array, relocate the first one to the prefix array
            if (!currentLeftArray.empty()) {
                prefixArray.push_back(currentLeftArray.front());
                currentLeftArray.erase(currentLeftArray.begin());
            }
        }

        // Return the answer
        return answer;
    }
};
