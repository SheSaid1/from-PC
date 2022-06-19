#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;



void ADD (vector <vector<string>>& m,int& i,string& s)
{
    m[i].push_back(s);
}


void DUMP (vector <vector<string>>& m,int& i)
{   cout<<  m[i].size() <<" ";
    for (const auto &j : m[i])
        cout<<j<<" ";
        cout<<endl;
}


void NEXT (vector <vector<string>>& m,int &p,vector <int>& mes )
{
    if (mes[p+1]>mes[p])
        m.resize(mes[p+1]+1);
    if (mes[p+1]<mes[p])
    {
        for (int i=0;i < mes[p]-mes[p+1];i++)
        {
       // cout<<"tut"<<endl;
        m[mes[p+1]].insert( end(m[mes[p+1]]),begin (m[mes[p+1]+1+i]),end(m[mes[p+1]+1+i] ));

        }
        m.resize(mes[p+1]+1);
    }
    p++;
    if(p>12)
        p=1;
}


int main ()
{   int n;
    int a;
    int day;
    vector < vector <string>> m(32);
    string delo;
    string s;
    cin>> n;
    int p=1;
    vector <int> mes = {0,31,28,31,30,31,30,31,31,30,31,30,31};

    for (int k=0;k<n;k++)
    {
       // cout <<"ya tut bil" <<endl;
       cin>> s;
       if (s=="ADD")
       {
           cin >> day;
           cin>> delo;
           ADD(m,day,delo);
       }
       if (s=="DUMP")
       {
           cin >> day;
           //cin>> delo;
           //cout<<endl;
           DUMP(m,day);
       }
        if (s=="NEXT")
       {
           //cin >> day;
           //cin>> delo;
           //cout<<endl;
           NEXT (m,p,mes);
       }




    }











    return 0;

}
