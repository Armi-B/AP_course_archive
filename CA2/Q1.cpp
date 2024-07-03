#include <iostream>
#include <vector>
#include <string>

using namespace std;

void max_or_min(int cur_ind, int last_one, int state);
vector<int> num;

int main ()
{
    int n, temp;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>temp;
        num.push_back(temp);
    }
    max_or_min(0,0,0);
    cout<<'\n';
    return 0;
}

void max_or_min(int cur_ind, int last_one, int state)
{
    if((cur_ind)>(size(num)-1))
    {
        return;
    }
    if(state==0)
    {
        cout<<num[cur_ind];
    }
    else
    {
    cout<<' '<<num[cur_ind];
    }
    int step;
    if(state%2==0)
    {
        if(num[cur_ind]<last_one)
        {
            step=last_one;
        }
        else
        {
            step=num[cur_ind];
        }
    }
    else
    {
        if(num[cur_ind]<last_one)
        {
            step=num[cur_ind];
        }
        else
        {
            step=last_one;
        }
    }
    if((num[cur_ind]==0&&step==0))
    {
        if(state!=0)
        {
            cout<<' '<<0;
        }
        return;
    }
    max_or_min((cur_ind+step), num[cur_ind],state+1);
}