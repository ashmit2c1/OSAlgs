#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

// Process class to represent each process
class Process {
public:
    int processID;        // ID of the process
    int arrivalTime;      // Arrival time of the process
    int burstTime;        // Burst time of the process
    int completionTime;   // Completion time of the process
    int waitingTime;      // Waiting time of the process
    int turnaroundTime;   // Turnaround time of the process

    // Constructor to initialize process attributes
    Process(int pid, int arrival, int burst)
        : processID(pid), arrivalTime(arrival), burstTime(burst),
          completionTime(0), waitingTime(0), turnaroundTime(0) {}
};

// SJFScheduler class to handle the scheduling
class SJFScheduler {
private:
    vector<Process> processes; // List of processes

public:
    // Function to add a process to the scheduler
    void addProcess(int pid, int arrival, int burst) {
        processes.emplace_back(pid, arrival, burst);
    }

    // Function to perform SJF scheduling
    void schedule() {
        int currentTime = 0;
        vector<bool> completed(processes.size(), false);
        int completedCount = 0;

        while (completedCount < processes.size()) {
            int shortestIndex = -1;
            int minBurstTime = INT_MAX;

            // Find the next process to execute
            for (size_t i = 0; i < processes.size(); ++i) {
                if (!completed[i] && processes[i].arrivalTime <= currentTime && processes[i].burstTime < minBurstTime) {
                    minBurstTime = processes[i].burstTime;
                    shortestIndex = i;
                }
            }

            // If no process has arrived, increment the current time
            if (shortestIndex == -1) {
                ++currentTime;
                continue;
            }

            // Process the selected process
            Process& process = processes[shortestIndex];
            process.completionTime = currentTime + process.burstTime;
            process.turnaroundTime = process.completionTime - process.arrivalTime;
            process.waitingTime = process.turnaroundTime - process.burstTime;
            currentTime = process.completionTime;
            completed[shortestIndex] = true;
            ++completedCount;
        }
    }

    // Function to display process information
    void display() const {
        cout << setw(10) << "Process ID"
             << setw(15) << "Arrival Time"
             << setw(10) << "Burst Time"
             << setw(15) << "Completion"
             << setw(15) << "Waiting Time"
             << setw(20) << "Turnaround Time\n";

        for (const auto& process : processes) {
            cout << setw(10) << process.processID
                 << setw(15) << process.arrivalTime
                 << setw(10) << process.burstTime
                 << setw(15) << process.completionTime
                 << setw(15) << process.waitingTime
                 << setw(20) << process.turnaroundTime << '\n';
        }
    }
};

int main() {
    // Create an instance of the scheduler
    SJFScheduler scheduler;

    // Add processes to the scheduler
    scheduler.addProcess(1, 0, 6);  // Process 1 with arrival time 0 and burst time 6
    scheduler.addProcess(2, 2, 8);  // Process 2 with arrival time 2 and burst time 8
    scheduler.addProcess(3, 4, 7);  // Process 3 with arrival time 4 and burst time 7
    scheduler.addProcess(4, 6, 3);  // Process 4 with arrival time 6 and burst time 3

    // Perform the scheduling
    scheduler.schedule();

    // Display the results
    scheduler.display();

    return 0;
}