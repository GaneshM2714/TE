#include "fcfs.h"     // Include headers for each scheduling algorithm
#include "sjf.h"
#include "rr.h"
#include "priority.h"
#include <iostream>
#include <limits>     // For clearing input buffer
#include <cstdlib>    // For exit()

int main() {
    int choice;
    int n;

    std::cout << "=== CPU Scheduling Algorithms ===" << std::endl;

    while (true) {
        std::cout << "\nChoose an algorithm:" << std::endl;
        std::cout << "1. First Come First Serve (FCFS)" << std::endl;
        std::cout << "2. Shortest Job First (SJF)" << std::endl;
        std::cout << "3. Round Robin (RR)" << std::endl;
        std::cout << "4. Priority Scheduling" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";

        cin>>choice;

        switch (choice) {
            case 1: {
                FCFS fcfs;
                fcfs.AT();
                fcfs.BT();
                
                break;
            }
            case 2: {
                SJF sjf;
                sjf.input();
                sjf.calculateCompletion();
                sjf.calculateTurnaround();
                sjf.calculateWaiting();
                sjf.displayMetrics();
                break;
            }
            case 3: {
               
                rr r;
                r.AT();
                r.BT();
                break;
            }
            case 4: {
                Priority priority;
                priority.AT();
                priority.BT();
                break;
            }
            case 5:
                std::cout << "Exiting..." << std::endl;
                exit(0);
            default:
                std::cout << "Invalid choice. Please enter a valid option (1-5)." << std::endl;
                break;
        }

        // Clear input buffer
        std::cin.clear();
    }

    return 0;
}
