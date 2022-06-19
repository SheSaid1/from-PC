#include <iostream>
using namespace std;


int main ()
{   int k1,M,K2,P2,N2;
    cin>>k1;
    cin>>M;
    cin>>K2;
    cin>>P2;
    cin>>N2;
    int x;
    int P1;
    int N1;
    //cout<< 198/36;
    if ((M*(P2-1)+N2-1)==0)
    {
        P1=0;
        if ( M==1)
        {
            N1=M;
            cout<<P1<<" "<<N1;
            return 0;
        }
        else {

            N1=0;
            cout<<P1<<" "<<N1;
        }
    }
    else {
     x=K2/(M*(P2-1)+N2-1);
     int y=K2/(M*(P2-1)+N2);
     if (y==0 || x<y)
     {
         cout<<-1<<" "<<-1;
         return 0;
     }
     P1=k1/(M*x) +1;
     if (k1%x==0)
        {
            N1=(k1-(P1-1)*M*x)/x;
            cout<<P1<<" "<<N1;
            }
     else
        {
            N1=(k1-(P1-1)*M*x)/x+1;
            cout<<P1<<" "<<N1;
            }


    }



    return 0;
}
