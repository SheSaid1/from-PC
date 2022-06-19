#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <locale>
#include <cctype>
#include <fstream>
#include <iomanip>


using namespace std;
void all( const map <string,vector<string>> &p )
{
    if(p.size()==0)
    {
        cout<<"No buses"<<endl;

    } else{
        for (const auto & y :p)
        {
            cout<<"Bus "<<y.first<<":";
            for (const auto& x: y.second)
            {
                cout<<" "<<x;
            }
            cout<<endl;
        }
    }
}

void bfs(const string&l ,const map <string,vector<string>> &p,const vector<string>& bus )
{
    int flag=0;
    vector<string> b;
    for (const auto& i:p)
    {
        for(const auto&j: i.second){
            if (j==l){
                b.push_back(i.first);
                flag=1;
            }
        }
    }
    if (flag!=0){
        for (const auto&i : bus){
            for (auto j: b){
                if (j==i){
                    cout<<i<<" ";
                }
            }
        }
    }
    else if (flag==0) {
            cout<<"No stop";
    }
    cout<<endl;
}

void sfb (const string&l ,const map <string,vector<string>> &p,const vector<string>& bus )
{
    int flag_1=0;
    for (auto i : p){
        if (i.first==l){
            for(auto j:i.second){
                cout<<"Stop "<<j<<":";
                int flag_2=0;
                vector<string>v;
                for(auto x: p){
                    for (auto y:x.second){
                        if(y==j &&x.first!=l){
                            v.push_back(x.first);
                            flag_2++;
                        }
                    }
                }
                if (flag_2==0){
                    cout<<" no interchange";
                }
                else if (flag_2!=0){
                    for (const auto& e: bus) {
                        for (auto w :v){
                            if (w==e){
                                cout<<" "<<e;
                            }
                        }
                    }
                }
                cout<<endl;
            }
            flag_1=1;
        }
    }
    if (flag_1==0)
        cout<<"No bus"<<endl;
}



map <string,vector<string>> povorot( map <string,vector<string>> p,map <int ,string> c)
{
     map <string,vector<string>> v;
     for (auto y: c)
             {
                 for ( auto k: p[y.second])
                 {
                     v[k].push_back(y.second);
                 }

             }
    return v;

}

int main()
{
    int q;
    cin>>q;

    vector <string> new_bus;
    map <string,vector <string>> bus_stops;
    //map <string,vector<string>> stops;
    int schet=1;
    //string bus;

    for (int i=0;i<q;i++)
    {   string operation_code,bus,stop;
          cin>>operation_code;
        if (operation_code=="NEW_BUS")
        { int col;
            cin>>bus>>col;
            new_bus.push_back(bus);
            for(int j=0;j<col;j++)
            {   string stop;
                cin>>stop;
                //table[bus].push_back(stop);
                bus_stops[bus].push_back(stop);
            }

        }
        if (operation_code=="BUSES_FOR_STOP")
        {   //int flag_1=0,flag_2=0;
           string stop;
           cin>>stop;
           bfs(stop,bus_stops,new_bus);

        }
        if (operation_code=="STOPS_FOR_BUS")
        {
            string bus;
            map <string,vector<string>> v;
            cin>>bus;
            sfb(bus,bus_stops,new_bus);


        }
        if (operation_code=="ALL_BUSES")
        {
            all(bus_stops);
        }

    }


    return 0;
}
