#include "Priority.h"
#include <algorithm> // for std::min_element
#include <climits>   // for INT_MAX
#include <iostream>

Priority::Priority() {
    std::cout << "Enter total processes: ";
    std::cin >> n;

    p.resize(n);
    at.resize(n);
    bt.resize(n);
    pr.resize(n);
    ct.resize(n);
    tat.resize(n);
    wt.resize(n);

    for (int i = 0; i < n; i++) {
        p[i] = i + 1;
    }
}

void Priority::AT() {
    std::cout << "Enter Arrival Times: ";
    for (auto &i : at)
        std::cin >> i;
}

void Priority::BT() {
    std::cout << "Enter Burst Times: ";
    for (auto &j : bt)
        std::cin >> j;

    PR();
}

void Priority::PR() {
    std::cout << "Enter Priorities (lower number means higher priority): ";
    for (auto &k : pr)
        std::cin >> k;

    CT();
}

void Priority::CT() {
    int curr_time = 0;
    std::vector<int> remaining_bt = bt; // Remaining burst time for each process
    int completed = 0;

    while (completed < n) {
        int idx = -1;
        int min_priority = INT_MAX;

        // Find the highest priority process that is ready to execute
        for (int j = 0; j < n; j++) {
            if (at[j] <= curr_time && remaining_bt[j] > 0 && pr[j] < min_priority) {
                min_priority = pr[j];
                idx = j;
            }
        }

        if (idx != -1) {
            // Execute the process for 1 time unit
            curr_time++;
            remaining_bt[idx]--;

            // If this process is completed
            if (remaining_bt[idx] == 0) {
                ct[idx] = curr_time;
                completed++;
            }
        } else {
            // If no process is ready, increment current time
            curr_time++;
        }
    }

    TAT();
}

void Priority::TAT() {
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
    }
    WT();
}

void Priority::WT() {
    for (int i = 0; i < n; i++) {
        wt[i] = tat[i] - bt[i];
    }

    displayTimes();
}

void Priority::displayTimes() {
    std::cout << "\nPriority Scheduling:\n";
    std::cout << "Process\tAT\tBT\tPr\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        std::cout << "P" << p[i] << "\t" << at[i] << "\t" << bt[i] << "\t"
                  << pr[i] << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
    }

    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        totalWT += wt[i];
        totalTAT += tat[i];
    }

    std::cout << "\nAverage Waiting Time: " << (totalWT / n) << std::endl;
    std::cout << "Average Turnaround Time: " << (totalTAT / n) << std::endl;
}
