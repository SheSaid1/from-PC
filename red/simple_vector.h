#pragma once

#include <cstdlib>

template <typename T>
class SimpleVector {
public:
  SimpleVector();
  explicit SimpleVector(size_t sizze);
  ~SimpleVector();

  T& operator[](size_t index);
  const T& operator[](size_t index) const ;

  T* begin();
  T* end();

  size_t Size() const;
  size_t Capacity() const;
  void PushBack(const T& value);

  const T* begin() const;
  const T* end() const;

private:
    T* Begin = nullptr;
    size_t cap;
    size_t size;
};



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
