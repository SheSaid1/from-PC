#include <vector>
#include <tuple>
#include <exception>
#include <cstddef>
#include <stdexcept>
#include <utility>
using namespace std;

template <class T>
class Deque {
public:
    Deque() {
        cap = 0;
        FFront = std::vector<T>(0);
        BBack = std::vector<T>(0);
    }
    bool Empty() const {
        return cap == 0 ? true : false;
    }
    size_t Size() const {
        return cap;
    }
    T& operator[](size_t i) {

    return i < FFront.size() ? FFront[FFront.size() - i - 1] : BBack[i - FFront.size()];
        }


    const  T& operator[](size_t i) const {
    return i < FFront.size() ? FFront[FFront.size() - i - 1] : BBack[i - FFront.size()];
    }
    T& At(size_t i) {
        if (i >= cap)
      throw out_of_range("Index is out of range");
    return i < FFront.size() ? FFront[FFront.size() - i - 1] : BBack[i - FFront.size()];

    }

         const T& At(size_t i) const {
        if (i >= cap)
        throw out_of_range("Index is out of range");
            return i < FFront.size() ? FFront[FFront.size() - i - 1] : BBack[i - FFront.size()];
        }


         const T& Front() const {
            return FFront.empty() ? BBack.front() : FFront.back();
        }
        T& Front() {
        return FFront.empty() ? BBack.front() : FFront.back();
        }
        T& Back() {
        return BBack.empty() ? FFront.front() : BBack.back();
        }

         const T& Back() const {
            return BBack.empty() ? FFront.front() : BBack.back();
        }
        void PushBack(T value) {
            BBack.push_back(value);
            cap++;
        }
        void PushFront(T value) {
            FFront.push_back(value);
            cap++;
        }




private:
    size_t cap;
    std::vector<T> FFront;
    std::vector<T> BBack;

};

/*
int main() {
    return 0;
}
*/
