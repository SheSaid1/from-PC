
/*
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;
*/
bool IsPalindrom (string v)
    {   int n=v.size();
    if (n==1) return 1;
    for (int i=0;i<n/2;i++)
    {
        if (v[i]!=v[n-1-i])
        {
            return 0;
        }
    }
     return 1;
         }


/*
int main ()
{
    //int 5;
    cout <<IsPalindrom ("nanbxan");

    return 0;
} */

