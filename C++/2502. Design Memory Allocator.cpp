#include <map>
#include <unordered_map>
#include <vector>

class Allocator {
public:
    // Constructor: Initializes the allocator with 'n' units of memory
    Allocator(int n) {
        tm[-1] = -1;  // Sentinel value for easier boundary handling
        tm[n] = n;    // End boundary
    }

    // Allocates 'size' units of memory for the given mID
    int allocate(int size, int mID) {
        int prevEnd = -1;  // Tracks the end of the previous allocated block
        for (auto &[currStart, currEnd] : tm) {
            // Calculate the start of the current free block
            int freeStart = prevEnd + 1;
            int freeEnd = currStart - 1;

            // Check if the free block is large enough
            if (freeEnd - freeStart + 1 >= size) {
                int allocStart = freeStart;
                tm[allocStart] = allocStart + size - 1;  // Mark the block as allocated
                d[mID].push_back(allocStart);           // Record the allocation for mID
                return allocStart;                      // Return the starting index
            }

            // Update the end of the previous allocated block
            prevEnd = currEnd;
        }
        return -1;  // No suitable block found
    }

    // Frees all memory allocated to the given mID
    int freeMemory(int mID) {
        int freed = 0;
        if (d.find(mID) != d.end()) {
            for (int start : d[mID]) {
                int end = tm[start];  // Get the end of the allocated block
                tm.erase(start);      // Remove the allocation from the map
                freed += end - start + 1;  // Add the size of the block to the total freed memory
            }
            d.erase(mID);  // Remove the mID entry from the map
        }
        return freed;  // Return the total amount of memory freed
    }

private:
    std::map<int, int> tm;  // Tracks allocated memory blocks (start -> end)
    std::unordered_map<int, std::vector<int>> d;  // Tracks allocations per mID (mID -> list of starts)
};
