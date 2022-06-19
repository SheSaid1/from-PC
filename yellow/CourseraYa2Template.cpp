//CourseraYa2Template.cpp

#include <iostream>
#include<map>
#include <vector>
#include <sstream>
#include <utility>
using namespace std;

template <typename First,typename Second>
ostream& operator <<(ostream & out, const pair <First,Second> &p)
{
    out<<p.frist<<","<<p.second;
    return out;
}


template <typename First, typename Second>
pair <First,Second> operator * ( const pair<First,Second>&p1,const pair<First,Second>&p2)
{
    First f=p1.first *p2.first;
    Second s=p1.second * p2.second;
    return make_pair (f,s);
}

template <typename T>
ostream & operator<<(ostream& out,const vector <T> vi)
{
    for (const auto &i : vi)
    {
        out<<i<<" ";
    }
    return out;
}

template <typename Key,typename Value>
ostream & operator<< (ostream& out,const map<Key,Value&vi)
{
    for(const auto &i : vi)
    {
        out<<i<<" ";
    }
    return out;
}

template <typename T>
T Sqr(T x )
{
    return x*x;
}

int main()
{   auto p=make_pair(2,3);
auto res=Sqr(p);
    cout<<res.first;
    cout<<endl;

    cout<<res.second;
    return 0;
}
