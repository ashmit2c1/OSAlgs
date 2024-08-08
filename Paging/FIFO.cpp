#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

// FIFOPageReplacement class to handle page replacement
class FIFOPageReplacement {
private:
    int numFrames;                // Number of frames available
    queue<int> pageQueue;         // Queue to store pages in memory
    unordered_set<int> pageSet;   // Set to track pages currently in frames
    int pageFaults;               // Count of page faults

public:
    // Constructor to initialize the number of frames
    FIFOPageReplacement(int frames) : numFrames(frames), pageFaults(0) {}

    // Function to process a page reference
    void processPage(int pageNumber) {
        // Check if the page is already in memory
        if (pageSet.find(pageNumber) == pageSet.end()) {
            // Page fault occurs
            ++pageFaults;

            // If memory is full, remove the oldest page
            if (pageQueue.size() == numFrames) {
                int oldestPage = pageQueue.front();
                pageQueue.pop();
                pageSet.erase(oldestPage);
            }

            // Add the new page to the memory
            pageQueue.push(pageNumber);
            pageSet.insert(pageNumber);
        }
    }

    // Function to get the number of page faults
    int getPageFaults() const {
        return pageFaults;
    }
};

int main() {
    // Define the number of frames
    int numFrames;
    cout << "Enter the number of frames: ";
    cin >> numFrames;

    // Create an instance of the FIFOPageReplacement
    FIFOPageReplacement fifo(numFrames);

    // Define the page reference string
    vector<int> pageReferences;
    int numReferences;
    cout << "Enter the number of page references: ";
    cin >> numReferences;
    cout << "Enter the page reference string: ";
    for (int i = 0; i < numReferences; ++i) {
        int page;
        cin >> page;
        pageReferences.push_back(page);
    }

    // Process each page reference
    for (int pageNumber : pageReferences) {
        fifo.processPage(pageNumber);
    }

    // Display the number of page faults
    cout << "Total page faults: " << fifo.getPageFaults() << endl;

    return 0;
}