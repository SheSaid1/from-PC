#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <list>
#include <unordered_map>
#include <tuple>
#include <queue>
#include <map>
#include <list>
using namespace std;

template <typename T>
struct Node
{
    T value;
    int prior = 0;
    int pos;
    //bool operator <

};
template <typename T>
bool operator <(const Node<T> &lhs,const  Node<T> &rhs) {
    if (lhs.prior == rhs.prior) {
        return lhs.pos < rhs.pos;
    }
    return lhs.prior < rhs.prior;
}
template <typename T>
bool operator == (const Node<T> &lhs,const  Node<T> &rhs) {
    return lhs.pos == rhs.pos;
}

template <typename T>
class PriorityCollection {
public:
    using Pair = std::pair <T, int>;
    using Id = int;



    Id Add(T object) {

    //S_.push_back({move(T), cnt});
    SET_.insert({move(object), 0, cnt});
    cnt++;
   // MAP_[T] = --(arr_.end());
    return cnt - 1;
  }


  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin) {

            while (range_begin != range_end) {
            SET_.insert({move(*range_begin), 0, cnt});
            range_begin++;
            cnt++;
            ids_begin.push_back(cnt - 1);
        }
    }

    bool IsValid(Id id) const {
        auto it = SET_.find({move(T()),0, id});
        return SET_.end() == it ? false : true;
  }

    const T& Get(Id id) const {
    auto it = SET_.find({move(T()),0, id});
    return it->value;
  }

    void Promote(Id id) {
        auto it = SET_.find({move(T()),0, id});
        //SET_.insert({move(it->value), move(it->prior + 1), move(it->pos)});
        Node<T> New(move(*it));
        New.prior += 1;
        SET_.insert(New);
        SET_.erase(it);
  }

  pair<const T&, int> GetMax() const;

  pair<T, int> PopMax();

private:
   /* std::priority_queue<Pair, std::list<Pair>,
        [](Pair x, Pair y) {
            return x.second < y.second;}; */
    int cnt = 0;
    std::set<Node<T>> SET_;
   // std::list<Pair> arr_;
    //std::unordered_map<T, Id> MAP_;
};


class StringNonCopyable : public string {
public:
  using string::string;  //
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

int main() {
  //TestRunner tr;
  //RUN_TEST(tr, TestNoCopy);
  return 0;
}
