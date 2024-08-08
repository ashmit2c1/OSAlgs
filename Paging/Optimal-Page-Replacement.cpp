#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iomanip>

using namespace std;

// OptimalPageReplacement class to handle page replacement
class OptimalPageReplacement {
private:
    int numFrames;                // Number of frames available
    vector<int> frames;           // Current pages in frames
    int pageFaults;               // Count of page faults

public:
    // Constructor to initialize the number of frames
    OptimalPageReplacement(int frames) : numFrames(frames), pageFaults(0) {
        this->frames = vector<int>(numFrames, -1);  // Initialize frames with -1 (empty)
    }

    // Function to find the optimal page to replace
    int findOptimalPageToReplace(const vector<int>& pageReferences, int currentIndex) {
        unordered_map<int, int> futureIndices;  // Map to store future index of each page in frames

        // Initialize future indices with a large number
        for (int i = 0; i < numFrames; ++i) {
            futureIndices[frames[i]] = INT_MAX;
        }

        // Find the next occurrence of each page in frames
        for (int i = currentIndex + 1; i < pageReferences.size(); ++i) {
            int page = pageReferences[i];
            if (futureIndices.find(page) != futureIndices.end() && futureIndices[page] == INT_MAX) {
                futureIndices[page] = i;  // Update future index
            }
        }

        // Find the page with the farthest future occurrence
        int maxFutureIndex = -1;
        int pageToReplace = -1;
        for (int i = 0; i < numFrames; ++i) {
            if (futureIndices[frames[i]] > maxFutureIndex) {
                maxFutureIndex = futureIndices[frames[i]];
                pageToReplace = i;
            }
        }
        return pageToReplace;
    }

    // Function to process a page reference
    void processPage(const vector<int>& pageReferences) {
        for (int i = 0; i < pageReferences.size(); ++i) {
            int pageNumber = pageReferences[i];

            // Check if the page is already in memory
            if (find(frames.begin(), frames.end(), pageNumber) == frames.end()) {
                // Page fault occurs
                ++pageFaults;

                // Check if there is space available in frames
                if (find(frames.begin(), frames.end(), -1) != frames.end()) {
                    // Fill empty frame
                    *find(frames.begin(), frames.end(), -1) = pageNumber;
                } else {
                    // Replace the optimal page
                    int replaceIndex = findOptimalPageToReplace(pageReferences, i);
                    frames[replaceIndex] = pageNumber;
                }
            }

            // Display current state of frames
            displayFrames();
        }
    }

    // Function to display the current frames
    void displayFrames() const {
        cout << "Frames: ";
        for (int page : frames) {
            if (page == -1) {
                cout << "E ";  // E represents an empty frame
            } else {
                cout << page << " ";
            }
        }
        cout << endl;
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

    // Create an instance of the OptimalPageReplacement
    OptimalPageReplacement optimal(numFrames);

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
    optimal.processPage(pageReferences);

    // Display the number of page faults
    cout << "Total page faults: " << optimal.getPageFaults() << endl;

    return 0;
}