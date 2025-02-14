#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include <numeric> // For std::gcd

class Solution {
public:
    // Function to count the number of factors of numbers 2-9 in t
    int count(long long t) {
        int ct = 0;
        for (int i = 9; i > 1; i--) {
            while (t % i == 0) {
                t /= i;
                ct++;
            }
        }
        // If t has factors outside 2-9, return INT_MAX
        if (t > 1) return INT_MAX;
        return ct;
    }

    // Function to create the smallest string with the given factors
    std::string SmallestString(long long t, int ct) {
        std::string ans(ct, ' ');
        ct--;
        for (int i = 9; i > 1; i--) {
            while (t % i == 0) {
                ans[ct--] = '0' + i;
                t /= i;
            }
        }
        return ans;
    }

    // Function to check if it's possible to create a greater number by replacing digits after ind
    bool CreateGreaterWithRest(const std::string& num, int ind, long long vl) {
        int ct = 0, n = num.size();
        std::vector<int> tp(10);
        // Factorize vl into digits 2-9
        for (int i = 9; i > 1; i--) {
            while (vl % i == 0) {
                tp[i]++;
                vl /= i;
                ct++;
            }
        }
        // Calculate how many extra positions are left after the current index and factor count
        int extraSpaces = n - ind - ct;
        tp[8] += tp[2] + tp[4];
        tp[2] = 0;
        tp[4] = 0;
        tp[9] += tp[3] + extraSpaces;
        tp[3] = 0;
        // Now, attempt to form a valid number starting from index ind in the string by replacing digits
        for (int i = 9; i >= 1; i--) {
            while (ind < n && tp[i] > 0) {
                // This means we can create a larger number
                if (i > num[ind] - '0') {
                    return true;
                }
                // Cannot create a larger number
                if (i < num[ind] - '0') {
                    return false;
                }
                ind++;
                tp[i]--;
            }
        }
        return true; // We can form a larger number
    }

    std::string smallestNumber(std::string num, long long t) {
        int n = num.size();
        int factcount = count(t);
        if (factcount == INT_MAX) return "-1";
        if (factcount > num.length()) {
            // If there are more factors than digits in num
            return SmallestString(t, factcount);
        }

        // Binary search to determine the smallest valid number
        long long l = 0, h = n, vl = -1, ans = -1;
        while (l <= h) {
            long long mid = (l + h) / 2;
            long long crt = t;
            bool zeroEncountered = false;
            // Check factors in the first mid digits
            for (int i = 0; i < mid; i++) {
                // Can't have a 0 dividing t
                if (num[i] == '0') {
                    h = i;
                    zeroEncountered = true;
                    break;
                }
                // Divide t by gcd of current digit
                crt /= std::gcd(crt, num[i] - '0');
            }
            if (zeroEncountered) continue;
            // If we can proceed with mid digits
            bool possible = false;
            if (mid == n) {
                if (crt == 1) return num;
            } else {
                // Check if we can create a valid number using the next digit
                for (int i = std::max(1, num[mid] - '0'); i < 10; i++) {
                    long long newT = crt / std::gcd(crt, i);
                    // Factors left
                    int positionsRequired = count(newT);
                    if (positionsRequired <= n - mid - 1 && (i > num[mid] - '0' || CreateGreaterWithRest(num, mid + 1, newT))) {
                        vl = i;
                        possible = true;
                        break;
                    }
                }
            }
            if (possible) {
                // Expand search space to the right
                l = mid + 1;
                ans = mid;
            } else {
                h = mid - 1;
            }
        }

        // Handle the result based on the search outcome
        long long crt = t;
        if (ans == -1) {
            // Add a leading zero to the number
            num = '0' + num;
            int ind = n;
            // Try to fill from the end with factors
            for (int j = 9; j > 0; j--) {
                while (ind > ans && crt % j == 0) {
                    num[ind--] = '0' + j;
                    crt /= j;
                }
            }
            return num;
        }
        // Replace the digit at the position ans
        num[ans] = '0' + vl;
        for (int i = 0; i <= ans; i++) {
            if (num[i] == '0') continue;
            // Reduce t by using gcd
            crt /= std::gcd(crt, num[i] - '0');
        }
        int ind = n - 1;
        for (int j = 9; j > 0; j--) {
            while (ind > ans && crt % j == 0) {
                num[ind--] = '0' + j;
                crt /= j;
            }
        }
        return num;
    }
};
```
