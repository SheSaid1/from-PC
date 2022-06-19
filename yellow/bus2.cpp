#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
using namespace std;



int main()
{
    int q;
    cin>>q;
    map<int,set<string>>  stop;
    for (int i=0;i<q;i++)
    {   int flag=0;
        int n;
        cin>>n;
        int value=stop.size();
        //cout<<"value is: "<<value;
        if (value==0){
                //int k=val
            for (int g=n;g>0;g--)
            {   string h;
                cin>>h;
                stop[value+1].insert(h);
            }
            cout<<"New bus "<<value+1<<endl;
        continue;
        }
        if (value>=1)
        {   string h;
            set <string> v;
            for(int g=n;g>0;g--){
                cin>> h;
                v.insert(h);
            }

            for (int k=value;k>0;k--){
                if(stop[k]==v)
                {
                    cout<<"Already exists for "<<k<<endl;
                    flag++;
                }
            }
            if (flag==0)
            {
                stop[value+1]=v;
                cout<<"New bus "<<value+1<<endl;
                //cout<<endl;
            }
            flag=0;

        }

    }
    return 0;
}
