#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string.h>
using namespace std;

class Process
{
public:
    int pid;
    int arrival_time;
    int burst_time;
    int process_type;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;

    void getdata()
    {
        cout<<"Enter the process ID : ";
        cin>>pid;
        cout<<"Enter arrival time of process "<<": ";
        cin>>arrival_time;
        cout<<"Enter burst time of process : ";
        cin>>burst_time;
        cout<<"Enter type of the process(press 1 if user process,press 2 if system process) :  ";
        cin>>process_type;

        cout<<endl;

    }
    void display()
    {
        cout<<pid<<"\t"<<arrival_time<<"\t"<<burst_time<<"\t"<<pt()<<"\t"
            <<completion_time<<"\t"<<turnaround_time<<"\t"<<waiting_time<<"\t"<<"\n"<<endl;


    }
    string pt()
    {
        if(process_type==1)
        {
            return "up";

        }
        else
        {
            return "sp";
        }

    }
};

void drawback(int cpu_utilisation)
{
    if(cpu_utilisation>80)
    {
        cout<<"For the given output the cpu utilization is "<<cpu_utilisation<<"% which is not so bad but for a giant number of process it will not work as good as doing now."<<endl;
    }
    else
    {
        cout<<"For the given output the cpu utilization is "<<cpu_utilisation <<"% which is This scheduling method is non-preemptive, that is the process will run until it finishes.Because of this non-preemptive scheduling, short processes which are at the back of the queue have to wait for the long process at the front to finishThroughput is not efficient.It is used in a small system only where I/O efficiency is not very important"<<endl;

    }

}

void findWaiting(Process p[], int n, int wt[])
{
	int rt[n];
	int pt=-1;

	for (int i = 0; i < n; i++)
		rt[i] = p[i].burst_time;

	int complete = 0, t = 0, minm = INT_MAX;
	int shortest = 0, finish_time;
	bool check = false;

	while (complete != n) {
		for (int j = 0; j < n; j++) {
			if ((p[j].arrival_time <= t) && (rt[j] < minm) && (rt[j] > 0) && (p[j].process_type<pt)) {
				minm = rt[j];
				shortest = j;
				check = true;
			}
		}

		if (check == false) {
			t++;
			continue;
		}

		rt[shortest]--;

		minm = rt[shortest];
		if (minm == 0)
			minm = INT_MAX;

		if (rt[shortest] == 0) {

			complete++;
			check = false;

			finish_time = t + 1;

			wt[shortest] = finish_time -
						p[shortest].burst_time -
						p[shortest].arrival_time;

			if (wt[shortest] < 0)
				wt[shortest] = 0;
		}
		t++;
	}
}

void findTurnAroundTime(Process p[], int n, int wt[], int tat[])
{
	for (int i = 0; i < n; i++)
		tat[i] = p[i].burst_time + wt[i];
}

void findavgTime(Process p[], int n)
{
	int wt[n], tat[n], total_wt = 0,
					total_tat = 0;

	findWaiting(p, n, wt);

	findTurnAroundTime(p, n, wt, tat);

	cout << "Processes\tBurst time\tWaiting time\t Turn around time\n";
	for (int i = 0; i < n; i++) {
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		cout << " " << p[i].pid << "\t\t"<< p[i].burst_time << "\t\t " << wt[i]<< "\t\t " << tat[i] << endl;
	}

	cout << "\nAverage waiting time = "
		<< (float)total_wt / (float)n;
	cout << "\nAverage turn around time = "
		<< (float)total_tat / (float)n;
}

Process p[100];

int main()
{
	int n;
	cout<<"Enter the number of the process : ";
	cin>>n;
	for(int i=0;i<n;i++)
    {
        p[i].getdata();
    }

	findavgTime(p, n);
	return 0;
}
