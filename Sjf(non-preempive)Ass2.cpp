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
    void display()
    {
        cout<<pid<<"\t"<<arrival_time<<"\t"<<burst_time<<"\t"<<pt()<<"\t"
            <<completion_time<<"\t"<<turnaround_time<<"\t"<<waiting_time<<"\t"<<"\n"<<endl;


    }


};

void drawback(int cpu_utilisation)
{
    if(cpu_utilisation>80)
    {
        cout<<"For the given output the cpu utilization is "<<cpu_utilisation<<"% which is not so bad but Job completion time must be known earlier, but it is hard to predict.It is often used in a batch system for long term scheduling."<<endl;
    }
    else{
        cout<<"For the given output the cpu utilization is "<<cpu_utilisation <<"% . SJF can't be implemented for CPU scheduling for the short term. It is because there is no specific method to predict the length of the upcoming CPU burst.This algorithm may cause very long turnaround times or starvation."<<endl;
    }

}


Process p[1000];


int cmp(Process p1, Process p2)
{
    if (p1.arrival_time == p2.arrival_time)
    {
        if(p1.process_type == p2.process_type)
        {
          return p1.burst_time>p2.burst_time;
        }
        return(p1.process_type < p2.process_type);
    }
    return (p1.arrival_time > p2.arrival_time);
}

void Sort(Process p[], int n)
{
    int i, j, k;
    Process key;
    for (j = 2; j <= n; j++)
    {
        key = p[j];
        i = j - 1;
        while (i > 0 && cmp(key, p[i]))
        {
            p[i + 1] = p[i];
            i = i - 1;
        }
        p[i + 1] = key;
    }
}


int main() {

    int n;
    float avg_turnaround_time;
    float avg_waiting_time;
    float cpu_utilisation;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_idle_time = 0;
    float throughput;
    int is_completed[100];
   // int pt[100];
    memset(is_completed,0,sizeof(is_completed));
   // memset(pt,1,sizeof(pt));


    cout << setprecision(2) << fixed;

    cout<<"Enter the number of processes: ";
    cin>>n;

    for(int i = 0; i < n; i++) {
        p[i].getdata();
    }

    int current_time = 0;
    int completed = 0;
    int prev = 0;

    while(completed != n) {
        Sort(p,n);
        int idx = -1;
        int mn = 10000000;
        for(int i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && is_completed[i] == 0 ) {
                if(p[i].burst_time < mn) {
                    mn = p[i].burst_time;
                    idx = i;
                }
                if(p[i].burst_time == mn) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mn = p[i].burst_time;
                        idx = i;
                    }
                }
            }
        }
        if(idx != -1) {
            p[idx].start_time = current_time;
            p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_idle_time += p[idx].start_time - prev;

            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].completion_time;
            prev = current_time;
        }
        else {
            current_time++;
        }
        n--;

    }

    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    for(int i = 0; i < n; i++) {
        min_arrival_time = min(min_arrival_time,p[i].arrival_time);
        max_completion_time = max(max_completion_time,p[i].completion_time);
    }

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    cpu_utilisation = ((max_completion_time - total_idle_time) / (float) max_completion_time )*100;

    cout<<endl<<endl;

    cout<<"#PID\t"<<"AT\t"<<"BT\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n"<<endl;

    for(int i = 0; i < n; i++) {
            p[i].display();
    }
    cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl;
    cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;
    drawback(cpu_utilisation);


}
