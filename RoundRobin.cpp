#include<iostream>
using namespace std;
struct Process{
int pid;
int arrivalTime;
int burstTime;
int completionTime;
int turnaroundTime;
int waitingTime;
};

void  CalculateTAT(Process Arr[],int n)
{
    for(int i = 0; i<n; i++)
    {
        Arr[i].turnaroundTime = Arr[i].completionTime - Arr[i].arrivalTime;
    }
}

void  CalculateWT(Process Arr[],int n)
{
    for(int i = 0; i<n; i++)
    {
        Arr[i].waitingTime = Arr[i].turnaroundTime - Arr[i].burstTime;
    }
}

void CalculateTime(Process Arr[], int n, int quantum)
{
    int R_time[n] = {0}; //Remaining time array

    for(int i = 0; i<n; i++)
    {
        R_time[i] = Arr[i].
        burstTime;  // copying burst time to decrement according to time quantum
    }

    int Curr_time = 0; //gant chart.
    bool Alldone = false; // keep track of all  completed processes

    while (!Alldone)
    {
        Alldone = true;
        for (int  i = 0; i < n; i++)
        {
            if(R_time[i] > 0)       //process decrement krta krta 0 pryant anaych ahe
            {
                Alldone = false;

                if(R_time[i] > quantum)
                {
                    Curr_time = Curr_time + quantum;
                    R_time[i] = R_time[i] - quantum;
                }
                else
                { 
                    
                    Curr_time = Curr_time + R_time[i];
                    Arr[i].completionTime = Curr_time;
                    R_time[i] = 0;
                }
            }
        }
        
        
    }
    
}

void DisplayResult(Process Arr[], int n)
{
    cout<<"-----------------------------------------------------------------------------------------------------"<<endl;
    cout<<"|  Process |  Arrival Time  |  Busrt Time  |  Completion Time  |  TurnAround Time  |  Waiting Time  |"<<endl;
    cout<<"-----------------------------------------------------------------------------------------------------"<<endl;
    for(int i = 0; i< n;i++)
    {
     cout<<"\t"<<Arr[i].pid<<"\t\t"<<Arr[i].arrivalTime<<"\t\t"<<Arr[i].burstTime<<"\t\t"<<Arr[i].completionTime<<"\t\t"<<Arr[i].turnaroundTime<<"\t\t\t"<<Arr[i].waitingTime<<endl;

    }
    cout<<"------------------------------------------------------------------------------------------------------"<<endl;
}

int main()
{
    int n,T_quantum;
    cout<<"\nEnter the number of processes :";
    cin>>n;

    cout<<"\nEnter the value of Time Quantum:";
    cin>>T_quantum;

    Process Arr[n];

    cout<<"\n\t-------Enter the process details---------";
    for(int i=0; i<n; i++)
    {
        cout<<"Process"<<i+1<<" :\n";
        Arr[i].pid = i+1;

        cout<<"   Arrival Time : ";
        cin>>Arr[i].arrivalTime;

        cout<<"  Burst Time : ";
        cin>>Arr[i].burstTime;

    }

    CalculateTime(Arr,n,T_quantum); // calculates the completion time according to 
    CalculateTAT(Arr,n);
    CalculateWT(Arr,n);
    DisplayResult(Arr,n);


    return 0;
}