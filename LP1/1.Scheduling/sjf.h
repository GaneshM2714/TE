#ifndef SJF_H
#define SJF_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>

class SJF {
private:
    int n;
    std::vector<int> at, bt, st, ct, tat, wt;

public:
    SJF();
    void input();
    void calculateCompletion();
    void calculateTurnaround();
    void calculateWaiting();
    void displayMetrics();
};

#endif // SJF_H
