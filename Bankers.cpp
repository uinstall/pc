#include<iostream>
using namespace std;

int main() {
    int n = 5;  // processes
    int r = 3;  // resources

    int Allocation[n][r]; // Allocation matrix
    int max[n][r];        // Max need matrix
    int available[r];

    cout << "\nEnter Allocation matrix :" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < r; j++) {
            cin >> Allocation[i][j]; // input Allocation matrix
        }
    }

    cout << "\nEnter Max Need matrix :" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < r; j++) {
            cin >> max[i][j]; // input max matrix
        }
    }

    cout << "\nEnter Available values :" << endl;
    for(int i = 0; i < r; i++) {
        cin >> available[i]; // input available values
    }

    int choice;
    cout << "Do you want to make a resource request? (1 for Yes / 0 for No): ";
    cin >> choice;

    if (choice == 1) {
        int request[r];

        cout << "\nEnter the Requested Resources for a process:" << endl;
        for(int i = 0; i < r; i++) {
            cin >> request[i]; // input requested resources
        }

        int processIndex;
        cout << "Enter the index of the process requesting resources (0 to " << n - 1 << "): ";
        cin >> processIndex;

        bool safe = true;
        for(int i = 0; i < r; i++) {
            if(request[i] > max[processIndex][i] - Allocation[processIndex][i] || request[i] > available[i]) {
                safe = false;
                break;
            }
        }

        if(safe) {
            // Temporarily allocating resources to check safety
            for(int i = 0; i < r; i++) {
                available[i] -= request[i];
                Allocation[processIndex][i] += request[i];
            }

            // Check safety for the resulting state
            int f[n] = {0}; // Resource allocation control
            int ans[n] = {0}; // Safe sequence storing purpose
            int ind = 0; // Safe sequence index store

            for(int k = 0; k < n; k++) { // for each process check need and all
                for(int i = 0; i < n; i++) {
                    if(f[i] == 0) {
                        int flag = 0;
                        for(int j = 0; j < r; j++) {
                            if(max[i][j] - Allocation[i][j] > available[j]) { // need is fulfilling or not
                                flag = 1;
                                break;
                            }
                        }

                        if(flag == 0) {
                            ans[ind++] = i; // safe sequence storing
                            for(int y = 0; y < r; y++) {
                                available[y] += Allocation[i][y]; // adding values after each completion
                            }
                            f[i] = 1; // entering safe sequence
                        }
                    }
                }
            }

            cout << "The safe sequence is :" << endl;
            for(int i = 0; i < n; i++) {
                cout << "P" << ans[i] << "-->";
            }

            cout << endl;
        } else {
            cout << "Request cannot be granted as it exceeds maximum need or available resources." << endl;
        }
    } else if (choice == 0) {
        // Finding safe sequence without a resource request
        int f[n] = {0}; // Resource allocation control
        int ans[n] = {0}; // Safe sequence storing purpose
        int ind = 0; // Safe sequence index store

        for(int k = 0; k < n; k++) { // for each process check need and all
            for(int i = 0; i < n; i++) {
                if(f[i] == 0) {
                    int flag = 0;
                    for(int j = 0; j < r; j++) {
                        if(max[i][j] - Allocation[i][j] > available[j]) { // need is fulfilling or not
                            flag = 1;
                            break;
                        }
                    }

                    if(flag == 0) {
                        ans[ind++] = i; // safe sequence storing
                        for(int y = 0; y < r; y++) {
                            available[y] += Allocation[i][y]; // adding values after each completion
                        }
                        f[i] = 1; // entering safe sequence
                    }
                }
            }
        }

        cout << "The safe sequence is :" << endl;
        for(int i = 0; i < n; i++) {
            cout << "P" << ans[i] << "-->";
        }

        cout << endl;
    } else {
        cout << "Invalid choice entered." << endl;
    }

    return 0;
}




/*
   Allocation   Max Need   available 
    001          763       232ss
    300          322
    100          802
    232          212
    003          523


*/
