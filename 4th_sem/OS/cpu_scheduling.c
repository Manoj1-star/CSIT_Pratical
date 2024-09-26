#include <stdio.h>

struct Process {
    int pid;              // Process ID
    int burst;            // Burst time
    int priority;         // Priority (used in Priority Scheduling)
    int waiting_time;     // Waiting time
    int turnaround_time;  // Turnaround time
};

// Function to calculate Turnaround Time
void calculate_TurnaroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst;
    }
}

// Function to calculate Waiting Time for FCFS
void calculate_FCFS(struct Process proc[], int n) {
    proc[0].waiting_time = 0; // First process has no waiting time
    for (int i = 1; i < n; i++) {
        proc[i].waiting_time = proc[i-1].waiting_time + proc[i-1].burst;
    }
}

// Function to calculate Waiting Time for SJF
void calculate_SJF(struct Process proc[], int n) {
    // Sort processes by burst time
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].burst > proc[j].burst) {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
    // Calculate waiting time like FCFS
    calculate_FCFS(proc, n);
}

// Function to calculate Waiting Time for Priority Scheduling
void calculate_priority(struct Process proc[], int n) {
    // Sort processes by priority
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].priority > proc[j].priority) {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
    // Calculate waiting time like FCFS
    calculate_FCFS(proc, n);
}

// Function to print results
void print_results(struct Process proc[], int n, const char* algo_name) {
    printf("\n%s Scheduling:\n", algo_name);
    printf("PID\tBurst\tPriority\tWaiting\tTurnaround\n");
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
        printf("%d\t%d\t%d\t\t%d\t%d\n", proc[i].pid, proc[i].burst, proc[i].priority, proc[i].waiting_time, proc[i].turnaround_time);
    }
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        printf("Enter burst time and priority for process %d: ", i + 1);
        proc[i].pid = i + 1;
        scanf("%d %d", &proc[i].burst, &proc[i].priority);
    }

    // FCFS
    calculate_FCFS(proc, n);
    calculate_TurnaroundTime(proc, n);
    print_results(proc, n, "FCFS");

    // SJF
    calculate_SJF(proc, n);
    calculate_TurnaroundTime(proc, n);
    print_results(proc, n, "SJF");

    // Priority
    calculate_priority(proc, n);
    calculate_TurnaroundTime(proc, n);
    print_results(proc, n, "Priority");

    return 0;
}

