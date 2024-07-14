#include "FCFS.h"
#include <algorithm> // for std::max
#include <cmath>     // for std::abs
#include <iostream>

FCFS::FCFS() {
    std::cout << "Enter total processes: ";
    std::cin >> n;

    at.resize(n, 0);
    bt.resize(n, 0);
    ct.resize(n, 0);
    tat.resize(n, 0);
    wt.resize(n, 0);
}

void FCFS::AT() {
    for (auto &i : at)
        std::cin >> i;
}

void FCFS::BT() {
    for (auto &j : bt)
        std::cin >> j;

    CT();
}

void FCFS::CT() {
    int curr_time = 0;

    for (int i = 0; i < n; i++) {
        ct[i] = std::max(curr_time, at[i]) + bt[i];
        curr_time = ct[i];
    }

    TAT();
}

void FCFS::TAT() {
    for (int i = 0; i < n; i++) {
        tat[i] = std::abs(ct[i] - at[i]);
    }
    WT();
}

void FCFS::WT() {
    for (int i = 0; i < n; i++) {
        wt[i] = std::abs(tat[i] - bt[i]);
    }

    display_times();
}

void FCFS::display_times() {
    std::cout << "Arrival Times: ";
    display(at);
    std::cout << "Burst Times: ";
    display(bt);
    std::cout << "Completion Times: ";
    display(ct);
    std::cout << "Turn Around Times: ";
    display(tat);
    std::cout << "Waiting Times: ";
    display(wt);
}

void FCFS::display(std::vector<int>& a) {
    for (auto& k : a) std::cout << k << "->";
    std::cout << std::endl;
}
