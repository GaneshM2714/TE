#ifndef RR_H
#define RR_H

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class rr {
public:
    int n, tq;  
    vector<int> at, bt, ct, tat, wt;

    rr();
    void AT();
    void BT();
    void CT();
    void TAT();
    void WT();
    void DisplayTimes();
};

#endif // RR_H
