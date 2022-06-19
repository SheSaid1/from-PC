#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
using namespace std;




map < char,int >  BuildCharCounters ( string & s)
{   map <char,int> result;
    for (const char & i : s)
    {
        ++result[i];
    }
    return result;
}


int main ()
{   int n;
    string a,b;
    cin >> n;
    for (int i=0;i<n;i++)
    {
        cin >> a>>b;
        if (BuildCharCounters(a)==BuildCharCounters(b))
            cout<<"YES"<<endl;
        else cout << "NO"<<endl;
    }



    return 0;
}
