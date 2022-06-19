#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
#include <deque>
#include <exception>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate() {
    if (Empty.size() == 0) {
        T* New = new T;
       // Cap.push_back(New);
        SET.insert(New);
        return New;
    }
    T* New = Empty.front();
    Empty.pop_front();
    SET.insert(New);
    return New;
  }
    T* TryAllocate()  {
     if (Empty.size() == 0) {
        return nullptr;
    }
    T* New = Empty.front();
    Empty.pop_front();
    SET.insert(New);
    return New;
  }

  void Deallocate(T* object) {
    auto it = SET.find(object);

    if (it == SET.end()) {
        throw invalid_argument("invalid argument");
    }
    SET.erase(it);
    Empty.push_back(object);
  }

  ~ObjectPool() {
  //  for (auto &i : Cap) {
      //  delete i;
   // }
    for (auto &i : Empty) {
       delete i;
    }
        for (auto &i : SET) {
        delete i;
    }
    //delete Empty;
  }

private:
    set<T*> SET;
  deque<T*> Empty;
  //deque<T*> Cap;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}


void print_container(const std::deque<int>& c)
{
    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';
}

int& kj (int &x) {
    x = x*2;
    return x;
}
int main() {
   /* std::deque<int> c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    print_container(c);
    auto it = find(c.begin(),c.end(), 2);
    auto it2 = it;
    c.erase(it);
    print_container(c);
    cout <<*it2<<endl; */

  TestRunner tr;
  int a = 5;
  int &x = kj(a);
  x +=1;


  cout << "a is " << a <<endl;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
