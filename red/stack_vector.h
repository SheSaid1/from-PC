#pragma once

#include <stdexcept>
#include <array>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0) {
    if (a_size > N) {
        throw invalid_argument("invalid argument");
    } else {
        array<T, N> V;
        Vector =  V;
        capacity = N;
        capacity_end = a_size;
        size = a_size;
    }

  }

  T& operator[](size_t index) {
    return *(this->begin() + index);
  }
  const T& operator[](size_t index) const {
    return *(this->begin() + index);
  }

  auto  begin() {
    return Vector.begin();
  }
  auto end() {
    return Vector.begin()+size;
  }
  auto const begin()const {
    return Vector.begin();
  }
  auto const end()const {
    return Vector.begin()+size;
  }

  size_t Size() const {
    return size;
  }
  size_t Capacity() const {
    return capacity;
  }

  void PushBack(const T& value) {
    if (size == capacity) {
        throw overflow_error("overflow");
    } else {
        *(this->begin() + size) = value;
        size++;
    }
  }
  T PopBack() {
    if (this->begin() == this->end()) {
        throw underflow_error("underflow");
    }
    size--;
    return *(this->begin() + size);
  }

private:
    array<T, N> Vector;
    size_t size;
    size_t capacity = N;
    size_t capacity_end;
};
