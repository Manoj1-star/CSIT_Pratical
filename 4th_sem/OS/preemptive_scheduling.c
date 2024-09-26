#include <stdio.h>

struct Process {
    int pid;              // Process ID
    int burst;            // Burst time
    int priority;         // Priority
    int arrival;          // Arrival time
    int waiting_time;     // Waiting time
    int turnaround_time;  // Turnaround time
    int remaining_time;   // Remaining burst time
    int completed;        // Process completion status
};

// Function to calculate waiting and turnaround time for Round Robin
void round_robin(struct Process proc[], int n, int quantum) {
    int time = 0;
    int completed_processes = 0;
    while (completed_processes < n) {
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0) {
                if (proc[i].remaining_time > quantum) {
                    time += quantum;
                    proc[i].remaining_time -= quantum;
                } else {
                    time += proc[i].remaining_time;
                    proc[i].waiting_time = time - proc[i].burst - proc[i].arrival;
                    proc[i].turnaround_time = time - proc[i].arrival;
                    proc[i].remaining_time = 0;
                    completed_processes++;
                }
            }
        }
    }
}

// Function to calculate waiting and turnaround time for Priority Scheduling
void preemptive_priority(struct Process proc[], int n) {
    int time = 0, completed_processes = 0, min_priority, current_process;

    while (completed_processes < n) {
        min_priority = 10000;  // Assigning high value initially for comparison
        current_process = -1;

        for (int i = 0; i < n; i++) {
            if (proc[i].arrival <= time && proc[i].remaining_time > 0 && proc[i].priority < min_priority) {
                min_priority = proc[i].priority;
                current_process = i;
            }
        }

        if (current_process != -1) {
            proc[current_process].remaining_time--;
            time++;

            if (proc[current_process].remaining_time == 0) {
                proc[current_process].waiting_time = time - proc[current_process].burst - proc[current_process].arrival;
                proc[current_process].turnaround_time = time - proc[current_process].arrival;
                completed_processes++;
            }
        } else {
            time++;  // No process ready, move to the next time unit
        }
    }
}

// Function to print results
void print_results(struct Process proc[], int n, const char* algo_name) {
    printf("\n%s Scheduling:\n", algo_name);
    printf("PID\tBurst\tPriority\tArrival\tWaiting\tTurnaround\n");
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
        printf("%d\t%d\t%d\t\t%d\t%d\t%d\n", proc[i].pid, proc[i].burst, proc[i].priority, proc[i].arrival, proc[i].waiting_time, proc[i].turnaround_time);
    }
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        printf("Enter burst time, priority and arrival time for process %d: ", i + 1);
        proc[i].pid = i + 1;
        scanf("%d %d %d", &proc[i].burst, &proc[i].priority, &proc[i].arrival);
        proc[i].remaining_time = proc[i].burst;
        proc[i].completed = 0;
    }

    // Round Robin
    printf("Enter time quantum for Round Robin: ");
    scanf("%d", &quantum);
    round_robin(proc, n, quantum);
    print_results(proc, n, "Round Robin");

    // Reset remaining time and completion status
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst;
        proc[i].completed = 0;
    }

    // Priority Scheduling
    preemptive_priority(proc, n);
    print_results(proc, n, "Preemptive Priority");

    return 0;
}
