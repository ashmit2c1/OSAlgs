#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

// LRUPageReplacement class to handle page replacement
class LRUPageReplacement {
private:
    int numFrames;                   // Number of frames available
    list<int> pageList;              // List to track the LRU order of pages
    unordered_map<int, list<int>::iterator> pageMap;  // Map to store references to the page in the list
    int pageFaults;                  // Count of page faults

public:
    // Constructor to initialize the number of frames
    LRUPageReplacement(int frames) : numFrames(frames), pageFaults(0) {}

    // Function to process a page reference
    void processPage(int pageNumber) {
        // Check if the page is already in memory
        if (pageMap.find(pageNumber) == pageMap.end()) {
            // Page fault occurs
            ++pageFaults;

            // If memory is full, remove the least recently used page
            if (pageList.size() == numFrames) {
                int lruPage = pageList.back();
                pageList.pop_back();
                pageMap.erase(lruPage);
            }
        } else {
            // Remove the page from its current position
            pageList.erase(pageMap[pageNumber]);
        }

        // Add the page to the front of the list
        pageList.push_front(pageNumber);
        pageMap[pageNumber] = pageList.begin();
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

    // Create an instance of the LRUPageReplacement
    LRUPageReplacement lru(numFrames);

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
        lru.processPage(pageNumber);
    }

    // Display the number of page faults
    cout << "Total page faults: " << lru.getPageFaults() << endl;

    return 0;
}