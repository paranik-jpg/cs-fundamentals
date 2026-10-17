#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>

struct Process {
    int id;
    int at;
    int bt;
    int remaining_bt;
    int ct = 0;
    int tat = 0;
    int wt = 0;
    int rt = -1;
};

void print_table(const std::string& algo_name, const std::vector<Process>& proc) {
    std::cout << "\n================ " << algo_name << " ================\n";
    std::cout << "PID\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    double total_tat = 0, total_wt = 0, total_rt = 0;

    for (const auto& p : proc) {
        std::cout << "P" << p.id << "\t"
                  << p.at << "\t"
                  << p.bt << "\t"
                  << p.ct << "\t"
                  << p.tat << "\t"
                  << p.wt << "\t"
                  << p.rt << "\n";
        total_tat += p.tat;
        total_wt += p.wt;
        total_rt += p.rt;
    }

    int n = proc.size();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average TAT: " << (total_tat / n) << "\n";
    std::cout << "Average WT : " << (total_wt / n) << "\n";
    std::cout << "Average RT : " << (total_rt / n) << "\n";
}

void srtf(std::vector<Process> proc) {
    int n = proc.size();
    int completed = 0;
    int current_time = 0;

    while (completed != n) {
        int best_idx = -1;
        int min_remaining = 1e9;

        // Pick process in ready queue with minimum remaining burst time
        for (int i = 0; i < n; ++i) {
            if (proc[i].at <= current_time && proc[i].remaining_bt > 0) {
                if (proc[i].remaining_bt < min_remaining) {
                    min_remaining = proc[i].remaining_bt;
                    best_idx = i;
                } else if (proc[i].remaining_bt == min_remaining) {
                    if (proc[i].at < proc[best_idx].at) {
                        best_idx = i;
                    }
                }
            }
        }

        if (best_idx == -1) {
            current_time++;
            continue;
        }

        // Record Response Time on first CPU grant
        if (proc[best_idx].rt == -1) {
            proc[best_idx].rt = current_time - proc[best_idx].at;
        }

        proc[best_idx].remaining_bt--;
        current_time++;

        if (proc[best_idx].remaining_bt == 0) {
            completed++;
            proc[best_idx].ct = current_time;
            proc[best_idx].tat = proc[best_idx].ct - proc[best_idx].at; // TAT = CT - AT
            proc[best_idx].wt = proc[best_idx].tat - proc[best_idx].bt; // WT = TAT - BT
        }
    }

    print_table("SRTF (Shortest Remaining Time First)", proc);
}

void round_robin(std::vector<Process> proc, int tq) {
    int n = proc.size();
    int current_time = 0;
    int completed = 0;
    std::queue<int> ready_queue;
    std::vector<bool> in_queue(n, false);

    // Initial check at t=0
    for (int i = 0; i < n; ++i) {
        if (proc[i].at <= current_time && !in_queue[i]) {
            ready_queue.push(i);
            in_queue[i] = true;
        }
    }

    while (completed != n) {
        if (ready_queue.empty()) {
            current_time++;
            for (int i = 0; i < n; ++i) {
                if (proc[i].at <= current_time && !in_queue[i]) {
                    ready_queue.push(i);
                    in_queue[i] = true;
                }
            }
            continue;
        }

        int idx = ready_queue.front();
        ready_queue.pop();

        if (proc[idx].rt == -1) {
            proc[idx].rt = current_time - proc[idx].at;
        }

        int exec_time = std::min(tq, proc[idx].remaining_bt);
        proc[idx].remaining_bt -= exec_time;
        current_time += exec_time;

        // Check for any newly arrived processes during this time slice
        for (int i = 0; i < n; ++i) {
            if (proc[i].at <= current_time && !in_queue[i] && proc[i].remaining_bt > 0) {
                ready_queue.push(i);
                in_queue[i] = true;
            }
        }

        // Re-enqueue current process if work remains, else mark complete
        if (proc[idx].remaining_bt > 0) {
            ready_queue.push(idx);
        } else {
            completed++;
            proc[idx].ct = current_time;
            proc[idx].tat = proc[idx].ct - proc[idx].at;
            proc[idx].wt = proc[idx].tat - proc[idx].bt;
        }
    }

    print_table("Round Robin (Time Quantum = 2)", proc);
}

int main() {
    std::vector<Process> input = {
        {1, 0, 5, 5},
        {2, 1, 3, 3},
        {3, 2, 1, 1},
        {4, 4, 2, 2}
    };

    srtf(input);
    round_robin(input, 2);

    return 0;
}
