#include "test_runner.h"

#include <algorithm>
#include <memory>
#include <vector>
#include <iterator>

using namespace std;

template <class T>
void Print (const T &v) {
    for (auto const &i : v) {
        std::cout << "\"" << i << "\"" << " " ;
    }
    std::cout << std::endl;
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
void Mergesort(RandomIt begin, RandomIt end) {
    auto size = static_cast<int>(std::distance(begin, end));
    if (size <= 1) {
        return;
    }
    auto middle = std::next(begin, size/2);
    Mergesort(begin, middle);
    Mergesort(middle, end);
    Merge(begin, middle,end);
}
*/

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    auto size = std::distance(range_begin, range_end);
    if (size <= 1) {
        return;
    }
    std::vector<typename RandomIt::value_type> v(
         make_move_iterator(range_begin),
         make_move_iterator(range_end)
         );
    auto part_1 = std::next(v.begin(),size/3);
    auto part_2 = std::next(v.begin(),2*size/3);
    MergeSort(v.begin(),part_1);
    MergeSort(part_1, part_2);
    MergeSort(part_2, v.end());
    std::vector<typename RandomIt::value_type> v1;
    std::merge(
        make_move_iterator (v.begin()),
        make_move_iterator (part_1),
        make_move_iterator (part_1),
        make_move_iterator (part_2),
        back_inserter(v1)
        );
    std::merge(
        make_move_iterator (v1.begin()),
        make_move_iterator (v1.end()),
        make_move_iterator (part_2),
        make_move_iterator (v.end()),
        range_begin
        );

    //Merge(v.begin(), part_1, part_2);
    //Merge(v.begin(), part_2, v.end());
}


void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  Print(numbers);
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
