#include <iostream>
#include <set>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
using namespace std;



void PrintSetReverse (const set<string> & s)
{
    vector<string> v (begin(s),end(s));
    for (int i=s.size();i>0;i--)
    {
        cout<<v[i-1]<<" ";
    }

    }


class Date
{
    public :

     Date(int new_year, int new_month, int new_day) {
    year = new_year;
    if (new_month > 12 || new_month < 1) {
      throw logic_error("Month value is invalid: " + to_string(new_month));
    }
    month = new_month;
    if (new_day > 31 || new_day < 1) {
      throw logic_error("Day value is invalid: " + to_string(new_day));
    }
    day = new_day;
  }

    int GetYear() const
    {return year; }
    int  GetMonth  () const
    {
        return month;
    }
    int GetDay() const
    {
        return day;
    }

     private:
    int year;
    int month;
    int day;
};
ostream& operator << (ostream &stream, const Date & date)
{
    stream<<setfill('0');
    stream<<setw(4)<<date.GetYear()<<"-"<<setw(2)<<date.GetMonth()<<"-"<<setw(2)<<date.GetDay();
    return stream;
}


bool operator < (const Date & lhs,const Date & rhs)
{
    return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
      vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}



class Event
{   void Find (const Date & date ){
    int n=DB[date].size();
    vector<string> v (begin(DB[date]),end(DB[date]));
    for (int i=n;i>0;i--)
    {
        cout<<v[i-1];
    }

    }
    void Print()
    {
        for (const auto &i : DB)
        {
            cout<<i.first<<" ";
            PrintSetReverse(i.second);
            cout<<endl;
        }
    }





    void Add (const Date & date, const string & event )
    {
        DB[date].insert(event);
    }
    void Del_event (const Date & date, const string & event )
    {
        if (DB[date].count(event)!=0)
            {
                DB[date].erase(event);
                cout<<"Deleted successfully"<<endl;

             }
        else
        {
            cout<<"Event not found"<<endl;
        }

    }
    void Del (const Date & date)
    {
        int n=DB[date].size();
        DB.erase(date);
       cout<<"Deleted"<<" "<<n<<" "<<"events";
    }
    private :
    map <Date, set<string>> DB;
};




int main()
{
    string operation_code;


    try { while (cin>>operation_code)

    {
        if(  operation_code!= "Add"  || operation_code!= "Del" || operation_code!="Print" || operation_code!="Fine")

            throw runtime_error(operation_code);
    }




    }
    catch (runtime_error & r)
    {
        cout<<r.what();
    }



    //Date date={2017,06,17};
    //PrintDate(date);
   // set <string> c= {"ab","ac","bc"};
    //PrintSetReverse(c);
    return 0;
}
