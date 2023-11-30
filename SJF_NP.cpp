#include <iostream>
#include <algorithm>
using namespace std;

struct process{
    int id;
    int at;
    int bt;
    int wt;
    int tat;
};

void calculate_wt(process p[],int n)
{
    p[0].wt=0;
    for(int i=1;i<n;++i)
    {
        p[i].wt=p[i-1].wt+p[i-1].bt;
    }
}

void calculate_tat(process p[],int n)
{

    for(int i=0;i<n;++i)
    {
        p[i].tat=p[i].wt+p[i].bt;
    }

}


bool comparebursttime(process a, process b)
{
    return a.bt<b.bt;
}


bool comparearrival(process a, process b)
{
    if(a.at==b.at)
    {
        return a.bt<b.bt;
    }
    
    return a.at<b.at;
    
}

void ganttchart(process p[], int n)
{
    int count_wt;
    int count_tat;
    for(int i=0;i<n;++i)
    {

        cout<<"P"<<p[i].id<<" | ";
        count_wt+=p[i].wt;
        count_tat+=p[i].tat;

    }
        cout<<"Avg WT:  "<<count_wt/n<<endl;
        cout<<"Avg TAT:  "<<count_tat/n<<endl;   


}



int main()
{
    cout<<"Enter the number of processes: ";
    int n;
    cin>>n;
    process p[n];

    for(int i=0;i<n;++i)
    {
        p[i].id=i+1;
        cout<<"Enter the arrival time: ";
        cin>>p[i].at;
        cout<<"Enter the burst time: ";
        cin>>p[i].bt;
    }

    sort(p,p+n,comparearrival);
    // sort(p, p + n, comparebursttime); // Sorting based on burst time (SJF) if all arrival times are the same

    calculate_wt(p,n);
    calculate_tat(p,n);

    cout<<"PID\tAT\tBT\tWT\tTAT\n";
	for(int i=0;i<n;++i)
	{
		cout<<p[i].id<<"\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].wt<<"\t"<<p[i].tat<<"\n"<<endl;
		
	}


    ganttchart(p,n);





}