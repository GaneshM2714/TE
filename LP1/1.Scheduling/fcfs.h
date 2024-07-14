#ifndef FCFS_H
#define FCFS_H

#include <iostream>
#include <vector>

class FCFS {
private:
    int n = 0;
    std::vector<int> at, bt, ct, tat, wt;

public:
    FCFS();
    void AT();
    void BT();
    void CT();
    void TAT();
    void WT();
    void display_times();
    void display(std::vector<int>& a);
};

#endif // FCFS_H
