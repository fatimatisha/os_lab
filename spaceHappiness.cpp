#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n,i,j,a[1000],sum=0,t,k;
    cin>>n;

    for(j=1; j<=n; j+=2)
    {
        if(j%2!=0)
        {
            sum=sum+j;

        }

    }

    for(k=n-1; k<=0; k--)
    {
        if(k%2!=0)
        {
            sum=sum+k;
        }
            cout<<sum<<endl;

    }
    cout<<sum<<endl;
}
