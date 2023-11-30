#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;   //Change only compareburst as a.pr < b.pr , take input, i+=pro[j].at-i;

class Process
{
	public:
	int at,bt,ct,ta,wt,btt,pr;
	string pro_id;
	/*
	artime = Arrival time,
	bt = Burst time,
	ct = Completion time,
	ta = Turn around time,
	wt = Waiting time
	*/


	static bool compareArrival(const Process& a, const Process& b) {
        return a.at < b.at;
    }

    static bool compareBurst(const Process& a, const Process& b) {
        return a.pr<b.pr;
    }
};

int main()
{
	Process pro[10];
	int n,i,j,pcom;

	cout<<"Enter the number of process::";
	cin>>n;
	cout<<"Enter the Process id arrival time burst time and priority :::";
	for(i=0;i<n;i++)
	{
		cin>>pro[i].pro_id;
		cin>>pro[i].at;
		cin>>pro[i].bt;
		pro[i].btt=pro[i].bt;
		cin>>pro[i].pr;
	}

	sort(pro,pro+n,Process::compareArrival);
	/*sort is a predefined funcion  defined in 
	algorithm.h header file, it will sort the 
	schedulees according to their arrival time*/

	i=0;
	pcom=0;
	while(pcom<n)
	{
		for(j=0;j<n;j++)
		{
			if(pro[j].at>i)
			break;
		}
		sort(pro,pro+j,Process::compareBurst);
		if(j>0)
		{
			for(j=0;j<n;j++)
			{
				if(pro[j].bt!=0)
				break;
			}
			if(pro[j].at>i)
			{
				i+=pro[j].at-i;
			}
	
			pro[j].ct=i+1;
			pro[j].bt--;
		}
		
		i++;
		pcom=0;
		for(j=0;j<n;j++)
		{
			if(pro[j].bt==0)
			pcom++;
		}
	}
    cout<<"ProID\tAtime\tBtime\tCtime\tTtime\tWtime\tPriority\n";
	for(i=0;i<n;i++)
	{
		pro[i].ta=pro[i].ct-pro[i].at;
		pro[i].wt=pro[i].ta-pro[i].btt;
		//before executing make it in one statement
		cout<<pro[i].pro_id<<"\t"<<pro[i].at<<"\t"<<pro[i].btt<<"\t"<<pro[i].ct<<"\t"<<pro[i].ta<<"\t"<<pro[i].wt<<"\t"<<pro[i].pr;
		cout<<endl;
	}

//calculating Average
	float wavg=0.0,tavg=0.0;
	for(int i=0;i<n;i++)
	{
		wavg+=pro[i].wt;
		tavg+=pro[i].ta;
	}
	
	cout<<"\n\nWT avg is "<<(float) wavg/n<<" & TAT avg is "<<(float) tavg/n;
	return 0;
}
