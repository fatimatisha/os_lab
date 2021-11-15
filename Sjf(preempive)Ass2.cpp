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

void sortWithProcess(Process p[],int n)
{
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            {
                if(p[i].process_type>p[i].process_type)
                {
                    Process temp=p[i];
                    p[i]=p[i+1];
                    p[i+1]=temp;
                }
            }
}

Process p[100];

int main()
{

    int n;
    float avg_turnaround_time;
    float avg_waiting_time;
    float cpu_utilisation;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    float throughput;
    int is_completed[100];
    memset(is_completed,0,sizeof(is_completed));


    cout << setprecision(2) << fixed;

    cout<<"Enter the number of processes: ";
    cin>>n;
    cout<<"\n";

    for(int i = 0; i < n; i++)
    {
        p[i].getdata();
    }


    int current_time = 0;
    int completed = 0;
    int prev = 0;

    while(completed != n)
    {
        int idx = -1;
        int mx = -1 ;
        int mn=100000;
        for(int i = 0; i < n; i++)
        {

            if(p[i].arrival_time <= current_time && is_completed[i] == 0)
            {
                sortWithProcess(p,n);
                if(p[i].process_type >mx)
                {

                    if(p[i].burst_time < mn)
                    {
                        mn = p[i].burst_time;
                        idx = i;
                    }
                    if(p[i].burst_time == mn)
                    {
                        if(p[i].arrival_time < p[idx].arrival_time)
                        {
                            mn = p[i].burst_time;
                            idx = i;
                        }
                    }
                    mx=i;
                }
                if(p[i].process_type == mx)
                {

                    if(p[i].burst_time < p[idx].burst_time)
                    {
                        mn = p[i].burst_time;
                        idx = i;
                    }
                    mx=i;
                }

            }
        }
        if(idx != -1)
        {
            p[idx].start_time = current_time;
            p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_response_time += p[idx].response_time;
            total_idle_time += p[idx].start_time - prev;

            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].completion_time;
            prev = current_time;
        }
        else
        {
            current_time++;
            cout<<"cpu is idle from "<<current_time<<"to "<<current_time+1<<endl;
        }
        n--;

    }


    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    for(int i = 0; i < n; i++)
    {
        min_arrival_time = min(min_arrival_time,p[i].arrival_time);
        max_completion_time = max(max_completion_time,p[i].completion_time);
    }

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    cpu_utilisation = ((max_completion_time - total_idle_time) / (float) max_completion_time )*100;
    throughput = float(n) / (max_completion_time - min_arrival_time);

    cout<<endl<<endl;

    cout<<"#PID\t"<<"AT\t"<<"BT\t"<<"PT\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n"<<endl;

    for(int i = 0; i < n; i++)
    {
        p[i].display();
    }
    cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl;
    cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;
    cout<<"\nDrawback of the Shortest Job First algorithm "<<endl;
    cout<<"-----------------------------------------------"<<endl;
    drawback(cpu_utilisation);

}

