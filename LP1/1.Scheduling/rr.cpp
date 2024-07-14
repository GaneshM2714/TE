#include "rr.h"

rr::rr() {
    cout << "Enter Total Processes: ";
    cin >> n;

    cout << "Enter Time Quantum: ";
    cin >> tq;

    at.resize(n, 0);
    bt.resize(n, 0);
    ct.resize(n, 0);
    tat.resize(n, 0);
    wt.resize(n, 0);
}

void rr::AT() {
    cout << "Enter Arrival Times: ";
    for (auto &i : at)
        cin >> i;
}

void rr::BT() {
    cout << "Enter Burst Times: ";
    for (auto &i : bt)
        cin >> i;

    CT();
}

void rr::CT() {
    queue<int> q;
    vector<bool> in_queue(n, false);
    int curr_time = 0;

    for (int i = 0; i < n; i++) {
        if (at[i] <= curr_time) {
            q.push(i);
            in_queue[i] = true;
        }
    }

    vector<int> remaining_bt = bt;
    int completed = 0;

    while (completed != n) {
        int idx = q.front();
        q.pop();
        in_queue[idx] = false;

        if (remaining_bt[idx] > tq) {
            curr_time += tq;
            remaining_bt[idx] -= tq;
        } else {
            curr_time += remaining_bt[idx];
            remaining_bt[idx] = 0;
            ct[idx] = curr_time;
            completed++;
        }

        for (int i = 0; i < n; i++) {
            if (idx == i) continue;
            if (at[i] <= curr_time && remaining_bt[i] != 0 && !in_queue[i]) {
                q.push(i);
                in_queue[i] = true;
            }
        }
    }
    TAT();
}

void rr::TAT() {
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
    }
    WT();
}

void rr::WT() {
    for (int i = 0; i < n; i++) {
        wt[i] = tat[i] - bt[i];
    }
    DisplayTimes();
}

void rr::DisplayTimes() {
    cout << "\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t" << at[i] << "\t" << bt[i] << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
    }
}
