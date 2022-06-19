#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <tuple>
#include <string>
#include <deque>
#include <stringstream>
using namespace std;

template <class T>
void Print (const T &v) {
    for (auto const &i : v) {
        std::cout << "\"" << i << "\"" << " " ;
    }
}


std::vector<std::string> SplitIntoWords(const std::string& s) {
    auto it = s.begin();
    auto Str_begin = s.begin();
    std::vector<std::string> result;
    while(it != s.end() ) {
        it = std::find(Str_begin, s.end(), ' ');
        result.push_back(std::string(Str_begin,it));
        Str_begin = it +1;
    }
    return result;
}

template <typename T>
void RemoveDuplicates(std::vector<T>& elements) {
    std::sort(elements.begin(), elements.end());
    auto it = std::unique(elements.begin(), elements.end());
    elements.erase(it,elements.end());
}

enum class Gender {
  FEMALE,
  MALE
};

struct Person {
  int age;  // возраст
  Gender gender;  // пол
  bool is_employed;  // имеет ли работу
};


template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  std::vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
  );
  return middle->age;
}

void PrintStats(std::vector<Person> persons) {
    auto beginn = persons.begin();
    auto endd = persons.end();
    std::cout << "Median age = " << ComputeMedianAge(beginn, endd) << '\n';
    auto it = std::partition(beginn, endd,
        [] (const Person &p) {
         return p.gender == Gender::FEMALE;}
        );
    std::cout << "Median age for females = " << ComputeMedianAge(beginn,it);
         it = std::partition(beginn, endd,
        [] (const Person &p) {
         return p.gender == Gender::MALE;}
        );
    std::cout << "Median age for males = " << ComputeMedianAge(beginn,it);

}
/*
template <typename RandomIt>   ///ругается на namespace???
void Merge(RandomIt begin, RandomIt middle, RandomIt end) {
    std::vector<typename  RandomIt::value_type> buffer;
    buffer.reserve(std::distance(begin, end));
    RandomIt left = begin;
    RandomIt right = middle;
    while (left != middle && right != end) {
        if (*left < *right) {
            buffer.emplace_back(*left);
            left++;
        } else {
             buffer.emplace_back(*right);
             right++;
        }
    }
    buffer.insert(buffer.end(), left, middle);
    buffer.insert(buffer.end(), right, end);
    std::move(buffer.begin(), buffer.end(), begin);

}


template <typename RandomIt>
void MergeSort(RandomIt begin, RandomIt end) {
    auto size = static_cast<int>(std::distance(begin, end));
    if (size <= 1) {
        return;
    }
    auto middle = std::next(begin, size/2);
    MergeSort(begin, middle);
    MergeSort(middle, end);
    Merge(begin, middle,end);
}
 */

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt begin, RandomIt end,
    char prefix) {
    std::string s(1, prefix);
    //std::cout << "s is " <<  s << "  pr is " << prefix << std::endl;
    auto left = std::lower_bound(begin, end,s);
    char next_prefix = static_cast<char>(prefix + 1);
    auto right = lower_bound(begin, end, std::string(1, next_prefix));

    return std::make_pair(left,right);

}

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt begin, RandomIt end,
    const string& s) {
    auto left = std::lower_bound(begin, end,s);
    char next_prefix = static_cast<char>(s[s.size() - 1] + 1);
    std::string new_string = s;
    new_string[s.size() - 1] = next_prefix;
    auto right = std::lower_bound(begin,end, new_string);
    return {left, right};

}
void A() {
    int x;
    std::cin >> x;
    int n;
    std::deque<string> DEQ;
    DEQ.push_back(to_string(x));
    std::cin >> n;
    std::string s;
    getline(cin, s);
    while (n > 0) {
   // std::cout << "tut";

    getline(cin, s);
    if (s[0] != '+' && s[0] != '-') {
        DEQ.push_back(" " + s);
    }
    else
    {
    DEQ.push_front("(");
    DEQ.push_back(") " + s); }
        --n;
    }
    std::string res = "";
    while (DEQ.size() > 0) {
        std::string k = DEQ.front();
        DEQ.pop_front();
        res += k;
    }
    std::cout << res;
}
void SendSms(const string& number, const string& message) {
  cout << "Send '" << message << "' to number " << number << endl;
}

void SendEmail(const string& email, const string& message) {
  cout << "Send '" << message << "' to e-mail "  << email << endl;
}

/*
 Реализуйте здесь классы INotifier, SmsNotifier, EmailNotifier
 */
 class INotifier{
public :
    INotifier() {}
    //INotifier (const string &s) : Note(s){};
    virtual void Notify(const string & message) const = 0;
private:
   // string Note;
 };
 class SmsNotifier : public INotifier {
public:
     SmsNotifier(const string &s) : number(s) {}
     virtual void Notify(const string & message) const override{
        SendSms(number,message);
     }

 private:
     const string number;
 };

 class EmailNotifier : public INotifier {
    public:
     EmailNotifier(const string &s) : email(s) {}
     virtual void Notify(const string & message) const override{
        SendEmail(email,message);
     }

 private:
     const string email;
 };

void Notify(INotifier& notifier, const string& message) {
  notifier.Notify(message);
}

class Figure {

virtual string Name() const  = 0;
virtual double Perimeter() const  = 0;
virtual double Area() const  = 0;
};
class Triangle : public Figure {
public:
    Triangle(int A,int B, int C) : a(A), b(B),c(C) {}
    virtual string Name() const override {
        return tri;
    }
    virtual double Perimeter() const override {
        double ans = a + b + c;
        return ans/ 2;
    }
    virtual double Area() const override {
        return 0;
    }
private:
   const  string tri = "TRIANGLE";
   int a;
   int b;
   int c;

};

class Circle : public Figure {
public:
    Circle (int r) : R(r) {}
    virtual string  Name() const override {
    return circle;
    }
    virtual double Area() const override {
        double ans = R*R;
        return ans*3.14;
    }
    virtual double Perimeter() const override{ return 0;}

private:
    const string circle = "CIRCLE";
    int R;

};


int main() {

  return 0;
}
