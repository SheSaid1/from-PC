#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
int GetDistinctRealRootCount(double a, double b, double c);

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

template <class A, class B, class C>
void AssertGet (const A&a, const B&b, const C&c, int ans, const string& hint = {}) {

}

void TestCount() {
    {
        int d =  GetDistinctRealRootCount(1, 2, 3);
        AssertEqual(d, 2, " d < 0" );
    }
        {
        int d =  GetDistinctRealRootCount(1, 2, 3);
        AssertEqual(d, 4, " d < 0" );
    }

}


class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    }
    /*catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    } */
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

int GetDistinctRealRootCount(double a, double b, double c) {
  // Вы можете вставлять сюда различные реализации функции,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
  return 3;
}


std::vector<std::string> Split(const std::string& str, const std::string& delimiter = " ") {  /// ���-�� �����  split �� Python
    std::vector<std::string> s;

    std::size_t pos = 0;
    std::size_t cond = str.find(delimiter, pos);
        if(cond == std::string::npos){
            s.push_back(str);
            return s;
        }
    int cnt = 0;
    while ( cond != std::string::npos && cnt < 1){
        std::string tmp = str.substr(pos,cond - pos);
        /*if (tmp != "") {
            s.push_back(tmp);
        }*/
        cnt++;
        s.push_back(tmp);
        pos = cond+delimiter.size();
        cond = str.find(delimiter, pos);
    }
        s.push_back(str.substr(pos, str.size()-1));

    return s;
}


class PhoneNumber {
public:
  /* ��������� ������ � ������� +XXX-YYY-ZZZZZZ
     ����� �� '+' �� ������� '-' - ��� ��� ������.
     ����� ����� ������ � ������ ��������� '-' - ��� ������
     ��, ��� ��� ����� ������� ������� '-' - ������� �����.
     ��� ������, ��� ������ � ������� ����� �� ������ ���� �������.
     ���� ������ �� ������������� ����� �������, ����� ��������� ���������� invalid_argument. ���������, ��� ����� �������� ������ �����, �� �����.

     �������:
     * +7-495-111-22-33
     * +7-495-1112233
     * +323-22-460002
     * +1-2-coursera-cpp
     * 1-2-333 - ������������ ����� - �� ���������� �� '+'
     * +7-1233 - ������������ ����� - ���� ������ ��� ������ � ������
  */
  explicit PhoneNumber(const string &international_number) {
        std::istringstream is(international_number);

        char sign = is.get();
        getline(is, country_code_,'-');
        getline(is, city_code_, '-');
        getline(is, local_number_);
        if ( sign != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty() ) {
            throw invalid_argument( " adsadsad" ) ;
        }

    }
    void Print() {
        std::cout << country_code_ << " " << city_code_ << " " << local_number_;
    }

  string GetCountryCode() const;
  string GetCityCode() const;
  string GetLocalNumber() const;
  string GetInternationalNumber() const;

private:
  string country_code_;
  string city_code_;
  string local_number_;
};

int main() {
    /*
  {TestRunner runner;
  runner.RunTest(TestCount, "testCount");
  }*/
  PhoneNumber a("+7-1233-213");
  std::cout << " all is ok " << '\n';
  a.Print();
  // добавьте сюда свои тесты
  //std::cout << " all is ok" ;
  return 0;
}
