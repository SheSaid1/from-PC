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

int nod(int a,int b)
{
    while (a>0 && b>0)
{
    if (a>b)
        a=a%b;
    else b=b%a;

}
    return a+b;
}

class Rational {
public:
  Rational() {
      p=0;
      q=1;}
    Rational (int num)
    {
        p=num;
        q=1;
    }
  Rational(int numerator, int denominator)
  {
      if (denominator==0)
      {
          throw invalid_argument("sd");
      }
      if (denominator <0)
      {
          numerator= numerator*(-1);

          denominator=denominator*(-1);

      }
      if (numerator==0)
      {
        p=0;
        q=1;


      } else if (numerator<0)
        {
            int c=nod(numerator*(-1),denominator);
            p=numerator/c;
            q=denominator/c;
        }
        else
        {
            int c=nod(numerator,denominator);
            p=numerator/c;
            q=denominator/c;
        }


  }

  int Numerator() const
  {
      return p;
  }
  int Denominator() const
  {
      return q;
  }
  void Sett(int numerator,int denominator)
  {
      if (denominator <0)
      {
          numerator= numerator*(-1);
          denominator=denominator*(-1);
      }
      if (numerator==0)
      {

          p=0;
          q=1;
      } else
      {

        int c=nod(numerator,denominator);
        p=numerator/c;
        q=denominator/c;
      }
  }

private :
    int p;
    int q;
};


bool operator == (Rational a, Rational b) {
    if ((a.Numerator() == b.Numerator()) && (a.Denominator() == b.Denominator())) {
        return true;
    }
    else {
        return false;
    }
}
Rational operator + (Rational a, Rational b) {
    int p = (a.Numerator() * b.Denominator()) + (b.Numerator() * a.Denominator());
    int q = a.Denominator() * b.Denominator();
    return Rational(p, q);
}
Rational operator - (Rational a, Rational b) {
    int p = (a.Numerator() * b.Denominator()) - (b.Numerator() * a.Denominator());
    int q = a.Denominator() * b.Denominator();
    return Rational(p, q);
}

Rational operator*(const Rational& lh,const Rational& rh)
{
    return Rational ( lh.Numerator()*rh.Numerator(), lh.Denominator()*rh.Denominator() );

}
Rational operator/(const Rational& lh,const Rational& rh)
{
    if (lh.Denominator()*rh.Numerator()==0)
    {
        throw domain_error("sadaa");
    }
    return Rational ( lh.Numerator()*rh.Denominator(), lh.Denominator()*rh.Numerator() );

}
/*

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
        "tut";
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}
*/
