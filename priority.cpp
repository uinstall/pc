#include <iostream>
#include <algorithm>
using namespace std;

struct process{
int id;
int wt;
int at;
int tat;
int bt;
int pr;
};

void calculate_wt(process p[], int n)
{
    p[0].wt=0;
    for(int i=1;i<n;++i)
    {
        p[i].wt=p[i-1].wt+p[i-1].bt;
    }
}

void calculate_tat(process p[], int n)
{
    for(int i=0;i<n;++i)
    {
        p[i].tat=p[i].wt+p[i].bt;
    }
}

void ganttchart(process p[], int n)
{
    int count_wt=0;
    int count_tat=0;
    for(int i=0;i<n;++i)
    {
        cout<<"P"<<p[i].id<<" | ";
        count_wt+=p[i].wt;
        count_tat+=p[i].tat;
    }

    cout<<"AVG WT: "<<count_wt/n<<endl;
    cout<<"AVG TAT: "<<count_tat/n<<endl;

}

bool compare_arrivaltime(process a, process b)
{
    if(a.at==b.at)
    {
        return a.pr<b.pr;
    }
    return a.at<b.at;
}




int main()
{
 cout << "Enter the number of processes: ";
    int n;
    cin >> n;
    process p[n];

    for (int i = 0; i < n; ++i) {
        p[i].id = i + 1;
        cout << "Enter the arrival time for process " << p[i].id << ": ";
        cin >> p[i].at;
        cout << "Enter the burst time for process " << p[i].id << ": ";
        cin >> p[i].bt;
        cout << "Enter the priority for process " << p[i].id << ": ";
        cin >> p[i].pr;
    }

    sort(p, p + n, compare_arrivaltime);
    calculate_wt(p, n);
    calculate_tat(p, n);


    cout << "PID\tAT\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; ++i) {
        cout << p[i].id << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].wt << "\t" << p[i].tat << "\t"<<endl;
    }

    ganttchart(p, n);

    return 0;



}