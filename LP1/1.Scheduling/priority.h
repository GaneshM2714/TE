#ifndef PRIORITY_H
#define PRIORITY_H

#include <iostream>
#include <vector>

class Priority {
private:
    int n = 0;
    std::vector<int> p, at, bt, pr, ct, tat, wt;

public:
    Priority();
    void AT();
    void BT();
    void PR();
    void CT();
    void TAT();
    void WT();
    void displayTimes();
};

#endif // PRIORITY_H
