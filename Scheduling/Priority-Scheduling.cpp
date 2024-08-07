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
    int priority;         // Priority of the process
    int completionTime;   // Completion time of the process
    int waitingTime;      // Waiting time of the process
    int turnaroundTime;   // Turnaround time of the process

    // Constructor to initialize process attributes
    Process(int pid, int arrival, int burst, int priority)
        : processID(pid), arrivalTime(arrival), burstTime(burst), priority(priority),
          completionTime(0), waitingTime(0), turnaroundTime(0) {}
};

// PriorityScheduler class to handle the scheduling
class PriorityScheduler {
private:
    vector<Process> processes; // List of processes

public:
    // Function to add a process to the scheduler
    void addProcess(int pid, int arrival, int burst, int priority) {
        processes.emplace_back(pid, arrival, burst, priority);
    }

    // Function to perform priority scheduling
    void schedule() {
        int currentTime = 0;
        vector<bool> completed(processes.size(), false);
        int completedCount = 0;

        while (completedCount < processes.size()) {
            int highestPriorityIndex = -1;
            int highestPriority = INT_MAX;

            // Find the process with the highest priority
            for (size_t i = 0; i < processes.size(); ++i) {
                if (!completed[i] && processes[i].arrivalTime <= currentTime &&
                    processes[i].priority < highestPriority) {
                    highestPriority = processes[i].priority;
                    highestPriorityIndex = i;
                }
            }

            // If no process is ready, increment the current time
            if (highestPriorityIndex == -1) {
                ++currentTime;
                continue;
            }

            // Process the selected process
            Process& process = processes[highestPriorityIndex];
            process.completionTime = currentTime + process.burstTime;
            process.turnaroundTime = process.completionTime - process.arrivalTime;
            process.waitingTime = process.turnaroundTime - process.burstTime;
            currentTime = process.completionTime;
            completed[highestPriorityIndex] = true;
            ++completedCount;
        }
    }

    // Function to display process information
    void display() const {
        cout << setw(10) << "Process ID"
             << setw(15) << "Arrival Time"
             << setw(10) << "Burst Time"
             << setw(10) << "Priority"
             << setw(15) << "Completion"
             << setw(15) << "Waiting Time"
             << setw(20) << "Turnaround Time\n";

        for (const auto& process : processes) {
            cout << setw(10) << process.processID
                 << setw(15) << process.arrivalTime
                 << setw(10) << process.burstTime
                 << setw(10) << process.priority
                 << setw(15) << process.completionTime
                 << setw(15) << process.waitingTime
                 << setw(20) << process.turnaroundTime << '\n';
        }
    }
};

int main() {
    // Create an instance of the scheduler
    PriorityScheduler scheduler;

    // Add processes to the scheduler
    scheduler.addProcess(1, 0, 3, 2);  // Process 1: arrival time 0, burst time 3, priority 2
    scheduler.addProcess(2, 2, 6, 1);  // Process 2: arrival time 2, burst time 6, priority 1
    scheduler.addProcess(3, 4, 4, 3);  // Process 3: arrival time 4, burst time 4, priority 3
    scheduler.addProcess(4, 6, 5, 2);  // Process 4: arrival time 6, burst time 5, priority 2
    scheduler.addProcess(5, 8, 2, 4);  // Process 5: arrival time 8, burst time 2, priority 4

    // Perform the scheduling
    scheduler.schedule();

    // Display the results
    scheduler.display();

    return 0;
}