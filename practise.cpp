#include<iostream>
#include<iomanip>

using namespace std;

 class Process{
 public:
    int pid;
    int arrival;
    int burst;
    int type;
    int turnarround;
    int completion;
    int waiting;
    int starttime;

    void getdata(){

        cout<<"Enter the process ID : ";
        cin>>pid;
        cout<<"Enter arrival time of process "<<": ";
        cin>>arrival ;
        cout<<"Enter burst time of process : ";
        cin>>burst ;
        cout<<"Enter type of the process(press 1 if user process,press 2 if system process) :  ";
        cin>>type ;

        cout<<endl;


    }
    void display(){

        cout<<pid<<"\t"<<arrival<<"\t"<<burst<<"\t"<<sp()<<"\t"<<turnarround<<"\t"<<completion<<"\t"<<waiting<<endl;
    }

    string sp(){
    if(type==1){
        return "up";
    }
    if(type==2)
    {
        return "sp";
    }
    }
 };


Process p[100];
int main()
{
    int n;
    float aturn,awaiting,aresponse,cpu_utilasation;
    int is_complete[100];
    int complete=0;
    int current=0;
    int prev=0;
    int tturn=0,twait=0,tresponse=0;
    memset(is_complete,0,sizeof(is_complete))

    cin>>n;
    for(int i=0;i<n;i++)
    {
        p[i].getdata();
    }

    cout<<"Gantt chart : "
    while(complete!=n){
    int idx=-1;
    int mx=-1
    for(int i=0;i<n;i++)
    {
        if(p[i].type>mx && is_complete[i]==0)
        {
            mx=p[i].type;
            idx=i;
        }
        if(p[i].type==mx)
        {

        }
    }
    }

}







