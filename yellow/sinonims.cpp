#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <map>
using namespace std;


int main ()
{
    int n;
    int flag=0,flag_2=0;
    string code_ask;
    string s_1,s_2;
    vector <string> v;
    set < set<string>> r;
    vector < set<string>> sett;
    map <string,int > mp;
    cin>>n;
    for (int i=0;i<n;i++)
    {
        cin>>code_ask;
        if (code_ask=="ADD")
        {   set <string> m;
            cin>>s_1>>s_2;
            m.insert(s_1);
            m.insert(s_2);
            if (r.count(m)==0)
            {
                r.insert(m);
                ++mp[s_1];
                ++mp[s_2];
            }

        }
        if (code_ask=="COUNT")
        {
            string word;
            cin>>word;
            /*
            int countt=0;
            for (auto i:  v)
            {
                if (i==word)
                    countt++;
            } */
            cout <<mp[word]<<endl;
        }
        if  (code_ask=="CHECK")
        {
            cin>>s_1>>s_2;
            set<string> l;
            l.insert(s_1);
            l.insert(s_2);
            if (r.count(l)==0)
                cout<<"NO"<<endl;
            else cout<<"YES" <<endl;
        }
    }

    return 0;
}
