#include "SJF.h"

SJF::SJF()  {
     std::cout << "Enter total processes: ";
    std::cin >> n;
    at.resize(n);
    bt.resize(n);
    st.resize(n);
    ct.resize(n);
    tat.resize(n);
    wt.resize(n);
}

void SJF::input() {
    for (int i = 0; i < n; i++) {
        std::cout << "Enter arrival time of process " << (i + 1) << ": ";
        std::cin >> at[i];
        std::cout << "Enter burst time of process " << (i + 1) << ": ";
        std::cin >> bt[i];
        std::cout << std::endl;
    }
}

void SJF::calculateCompletion() {
    std::vector<bool> completed(n, false);
    int ct_curr = 0;
    int completed_count = 0;

    while (completed_count < n) {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (at[i] <= ct_curr && !completed[i]) {
                if (idx == -1 || bt[i] < bt[idx] ||
                    (bt[i] == bt[idx] && at[i] < at[idx])) {
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            st[idx] = ct_curr;
            ct[idx] = st[idx] + bt[idx];
            completed[idx] = true;
            completed_count++;
            ct_curr = ct[idx];
        } else {
            ct_curr++;
        }
    }
}

void SJF::calculateTurnaround() {
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
    }
}

void SJF::calculateWaiting() {
    for (int i = 0; i < n; i++) {
        wt[i] = tat[i] - bt[i];
    }
}

void SJF::displayMetrics() {
    int total_tat = 0, total_wt = 0;

    std::cout << std::endl << std::endl;
    std::cout << "#P\tAT\tBT\tST\tCT\tTAT\tWT\n" << std::endl;

    for (int i = 0; i < n; i++) {
        std::cout << (i + 1) << "\t" << at[i] << "\t" << bt[i] << "\t"
                  << st[i] << "\t" << ct[i] << "\t"
                  << tat[i] << "\t" << wt[i] << "\n" << std::endl;
        total_tat += tat[i];
        total_wt += wt[i];
    }

    float avg_tat = static_cast<float>(total_tat) / n;
    float avg_wt = static_cast<float>(total_wt) / n;

    std::cout << "Average Turnaround Time = " << avg_tat << std::endl;
    std::cout << "Average Waiting Time = " << avg_wt << std::endl;
}
