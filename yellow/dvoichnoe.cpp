#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

int main() {
int a;
vector<int> v;
cin >> a;
//for (int i=a;i!=0;i/2)
while (a!=1)
{ // cout<<a <<endl;
    v.push_back(a%2);
    a /=2;
}
v.push_back(1);
for (int i=v.size();i>0;i--)
{

 cout<<v[i-1];

 }

return 0;
}

