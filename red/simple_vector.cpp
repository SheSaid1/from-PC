
#include "simple_vector.h"
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <typename T>
SimpleVector<T>:: SimpleVector()
    : Begin(nullptr)
    , size(0)
    , cap(0) {}

template <typename T>
SimpleVector<T>:: ~SimpleVector() {
    delete[] Begin;
}


template <typename T>
SimpleVector<T>:: SimpleVector(size_t sizze) {
    T* it = new T[sizze];
    Begin = it;
    //Begin[0] = 1;
    size = sizze;
    cap = sizze;
}

template <typename T>
size_t SimpleVector<T>::Size() const {
    return size;
}

template <typename T>
size_t SimpleVector<T>::Capacity() const {
    return cap;
}

template <typename T>
void SimpleVector<T>::PushBack(const T& value){
    if (size == cap && size >= 1) {
        T* New = new T[cap*2];
        cap *= 2;
        for (int i = 0; i < size; ++i) {
            New[i] = Begin[i];
        }

        New[size] = value;
        size++;
        delete[] Begin;
        Begin = New;

        return;
    }

    if (size == cap && size == 0) {
        size  = 1;
        cap = 1;
        T* New = new T[1];
        New[0] = value;
        Begin = New;
        return;
    }
    Begin[size] = value;
    size++;
}

template <typename T>
T& SimpleVector<T>::operator[](size_t index) {
    return *(Begin + index);
}
template <typename T>
const T& SimpleVector<T>::operator[](size_t index) const {
    return *(Begin + index);
}

template <typename T>
T* SimpleVector<T>::begin() {
    return Begin;
}

template <typename T>
const T* SimpleVector<T>::begin() const  {
    return Begin;
}

template <typename T>
const T* SimpleVector<T>::end() const  {
    return Begin + size;
}

template <typename T>
 T* SimpleVector<T>::end() {
    return Begin + size;
}

void TestConstruction() {
  SimpleVector<int> empty;
  ASSERT_EQUAL(empty.Size(), 0u);
  ASSERT_EQUAL(empty.Capacity(), 0u);
  ASSERT(empty.begin() == empty.end());

  SimpleVector<string> five_strings(5);
  ASSERT_EQUAL(five_strings.Size(), 5u);
  ASSERT(five_strings.Size() <= five_strings.Capacity());
  for (auto& item : five_strings) {
    ASSERT(item.empty());
  }
  five_strings[2] = "Hello";
  ASSERT_EQUAL(five_strings[2], "Hello");
}

void TestPushBack() {
  SimpleVector<int> v;
  for (int i = 10; i >= 1; --i) {
    v.PushBack(i);
    ASSERT(v.Size() <= v.Capacity());
  }
  sort(begin(v), end(v));

  const vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQUAL(v.Size(), expected.size());
  ASSERT(equal(begin(v), end(v), begin(expected)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestConstruction);
  RUN_TEST(tr, TestPushBack);
  return 0;
}
