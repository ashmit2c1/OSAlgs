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

// FCFSScheduler class to handle the scheduling
class FCFSScheduler {
private:
    vector<Process> processes; // List of processes

public:
    // Function to add a process to the scheduler
    void addProcess(int pid, int arrival, int burst) {
        processes.emplace_back(pid, arrival, burst);
    }

    // Function to perform FCFS scheduling
    void schedule() {
        int currentTime = 0;

        // Sort processes by arrival time
        sort(processes.begin(), processes.end(),
             [](const Process& a, const Process& b) {
                 return a.arrivalTime < b.arrivalTime;
             });

        for (auto& process : processes) {
            // Wait until the process arrives
            if (currentTime < process.arrivalTime) {
                currentTime = process.arrivalTime;
            }

            // Calculate completion time
            process.completionTime = currentTime + process.burstTime;

            // Calculate turnaround time
            process.turnaroundTime = process.completionTime - process.arrivalTime;

            // Calculate waiting time
            process.waitingTime = process.turnaroundTime - process.burstTime;

            // Update current time
            currentTime = process.completionTime;
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
    FCFSScheduler scheduler;

    // Add processes to the scheduler
    scheduler.addProcess(1, 0, 4);  // Process 1 with arrival time 0 and burst time 4
    scheduler.addProcess(2, 1, 3);  // Process 2 with arrival time 1 and burst time 3
    scheduler.addProcess(3, 2, 1);  // Process 3 with arrival time 2 and burst time 1
    scheduler.addProcess(4, 3, 2);  // Process 4 with arrival time 3 and burst time 2
    scheduler.addProcess(5, 4, 5);  // Process 5 with arrival time 4 and burst time 5

    // Perform the scheduling
    scheduler.schedule();

    // Display the results
    scheduler.display();

    return 0;
}