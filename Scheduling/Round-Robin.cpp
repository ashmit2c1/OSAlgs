#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>

using namespace std;

// Process class to represent each process
class Process {
public:
    int processID;        // ID of the process
    int arrivalTime;      // Arrival time of the process
    int burstTime;        // Burst time of the process
    int remainingTime;    // Remaining time of the process
    int completionTime;   // Completion time of the process
    int waitingTime;      // Waiting time of the process
    int turnaroundTime;   // Turnaround time of the process

    // Constructor to initialize process attributes
    Process(int pid, int arrival, int burst)
        : processID(pid), arrivalTime(arrival), burstTime(burst), remainingTime(burst),
          completionTime(0), waitingTime(0), turnaroundTime(0) {}
};

// RoundRobinScheduler class to handle the scheduling
class RoundRobinScheduler {
private:
    vector<Process> processes; // List of processes
    int timeQuantum;           // Time quantum for each process

public:
    // Constructor to initialize time quantum
    RoundRobinScheduler(int tq) : timeQuantum(tq) {}

    // Function to add a process to the scheduler
    void addProcess(int pid, int arrival, int burst) {
        processes.emplace_back(pid, arrival, burst);
    }

    // Function to perform round-robin scheduling
    void schedule() {
        queue<int> readyQueue;    // Queue to manage the ready processes
        int currentTime = 0;      // Current time in the system
        int completedCount = 0;   // Number of processes completed
        vector<bool> inQueue(processes.size(), false);  // Track processes in the queue

        while (completedCount < processes.size()) {
            // Add new arrivals to the queue
            for (size_t i = 0; i < processes.size(); ++i) {
                if (!inQueue[i] && processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                    readyQueue.push(i);
                    inQueue[i] = true;
                }
            }

            if (readyQueue.empty()) {
                ++currentTime;
                continue;
            }

            // Get the next process from the queue
            int index = readyQueue.front();
            readyQueue.pop();

            Process& process = processes[index];

            // Execute the process for the time quantum or until completion
            int executionTime = min(timeQuantum, process.remainingTime);
            process.remainingTime -= executionTime;
            currentTime += executionTime;

            // Add new arrivals to the queue during execution
            for (size_t i = 0; i < processes.size(); ++i) {
                if (!inQueue[i] && processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                    readyQueue.push(i);
                    inQueue[i] = true;
                }
            }

            // If the process is not completed, add it back to the queue
            if (process.remainingTime > 0) {
                readyQueue.push(index);
            } else {
                // Process has completed
                process.completionTime = currentTime;
                process.turnaroundTime = process.completionTime - process.arrivalTime;
                process.waitingTime = process.turnaroundTime - process.burstTime;
                ++completedCount;
            }
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
    int timeQuantum;
    cout << "Enter the time quantum: ";
    cin >> timeQuantum;

    // Create an instance of the scheduler
    RoundRobinScheduler scheduler(timeQuantum);

    // Add processes to the scheduler
    scheduler.addProcess(1, 0, 5);  // Process 1: arrival time 0, burst time 5
    scheduler.addProcess(2, 1, 3);  // Process 2: arrival time 1, burst time 3
    scheduler.addProcess(3, 2, 8);  // Process 3: arrival time 2, burst time 8
    scheduler.addProcess(4, 3, 6);  // Process 4: arrival time 3, burst time 6

    // Perform the scheduling
    scheduler.schedule();

    // Display the results
    scheduler.display();

    return 0;
}