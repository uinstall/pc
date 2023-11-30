#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Process {
    int id;
    int at;
    int bt;
    int rt; // Remaining time (New addition)
    int wt;
    int tat;
};

bool compareArrival(const Process& a, const Process& b) {
    return a.at < b.at;
}

// Function to find the next process to execute based on shortest remaining time
int findNextProcess(const vector<Process>& processes, int currentTime) {
    int minRemainingTime = INT_MAX;
    int nextProcess = -1;

    for (int i = 0; i < processes.size(); ++i) {
        if (processes[i].rt > 0 && processes[i].at <= currentTime && processes[i].rt < minRemainingTime) {
            minRemainingTime = processes[i].rt;
            nextProcess = i;
        }
    }

    return nextProcess;
}

// Function to simulate process scheduling and calculate waiting and turnaround times
void calculateTimes(vector<Process>& processes) {
    int currentTime = 0;
    int completed = 0;
    vector<int> ganttChart;

    while (completed != processes.size()) {
        int nextProcess = findNextProcess(processes, currentTime);

        if (nextProcess == -1) {
            currentTime++;
            continue;
        }

        processes[nextProcess].rt--; // Decrement remaining time for the selected process

        ganttChart.push_back(processes[nextProcess].id); // Store executed process ID in Gantt Chart

        if (processes[nextProcess].rt == 0) {
            completed++;
            int finishTime = currentTime + 1;
            processes[nextProcess].tat = finishTime - processes[nextProcess].at; // Calculate Turnaround Time
            processes[nextProcess].wt = processes[nextProcess].tat - processes[nextProcess].bt; // Calculate Waiting Time
        }

        currentTime++;
    }



// Printing Gantt Chart
cout << "Gantt Chart: ";
for (size_t i = 0; i < ganttChart.size(); ++i) {
    cout << "P" << ganttChart[i] << " | ";
}
cout << endl;

}

int main() {
    cout << "Enter the number of processes: ";
    int n;
    cin >> n;
    vector<Process> processes(n);

    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter the arrival time for process " << i + 1 << ": ";
        cin >> processes[i].at;
        cout << "Enter the burst time for process " << i + 1 << ": ";
        cin >> processes[i].bt;
        processes[i].rt = processes[i].bt; // Set remaining time initially to burst time
    }

    sort(processes.begin(), processes.end(), compareArrival); // Sort processes by arrival time

    calculateTimes(processes); // Perform scheduling and calculations

    // Display process details including ID, Arrival Time, Burst Time, Waiting Time, Turnaround Time
    cout << "PID\tAT\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; ++i) {
        cout << processes[i].id << "\t" << processes[i].at << "\t"
             << processes[i].bt << "\t" << processes[i].wt << "\t"
             << processes[i].tat << "\n";
    }

    return 0;
}
