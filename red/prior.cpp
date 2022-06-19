
#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <map>
#include <list>
#include <unordered_map>
using namespace std;

struct Node {
    int id  ;
    int prior = 0;
};


/*bool operator == (const Node&lhs,const Node&rhs) {
    return lhs.id == rhs.id;
}*/
bool operator < (const Node&lhs,const Node&rhs) {
    if (lhs.prior == rhs.prior) {
        return lhs.id < rhs.id;
    }
    return lhs.prior < rhs.prior;
}
bool operator > (const Node&lhs,const Node&rhs) {
    if (lhs.prior == rhs.prior) {
        return lhs.id > rhs.id;
    }
    return lhs.prior > rhs.prior;
}

template <typename T>
class PriorityCollection {
public:
    using Id = int;
    using Idd = list<Node>::iterator;


  Id Add(T object) {
    //MAP_[pos] = move(object);
    //pos =
    Node N {pos,0};
    LIST_.push_back(move(N));
    MAP_2[pos] = --LIST_.end();
    MAP_[pos] = move(object);
    pos++;
    return pos - 1;
  }


    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin) {
        list<Id> V;
        while(range_begin != range_end) {
            //MAP_[pos] = move(*range_begin);
            //LIST_.push_back({pos,0});
            Node N {pos,0};
            LIST_.push_back(move(N));
            V.push_back( pos);
            //MAP_[] =
            MAP_2[pos] = --LIST_.end();
            MAP_[pos] = move(*range_begin);
            pos++;
            range_begin++;
        }
        move(V.begin(), V.end(),ids_begin);

    }


    bool IsValid(Id id) const {

        return MAP_.find(id) != MAP_.end() ? true : false;
  }

    const T& Get(Id id) const {
        return MAP_.at(id);
  }

    void Promote(Id ID) {
   // MAP_2[ID]->prior += 1;
    Node New {ID, MAP_2[ID]->prior + 1};
    LIST_.erase(MAP_2[ID]);
    auto it = --LIST_.end();
    while (it != LIST_.begin() && New < *it) {
        //ID.swap(it);
        it--;
    }
    if (it == LIST_.begin() && New < *it) {
        LIST_.push_front(New);
        MAP_2[ID] = LIST_.begin();
        return;
    }
    it++;
    MAP_2[ID] = LIST_.insert(it, New);

  }

    pair<const T&, int> GetMax() const {
        auto ID = LIST_.back().id;
        return {MAP_.at(ID), LIST_.back().prior};
  }

    pair<T, int> PopMax() {
        auto ID = LIST_.back().id;
        int PRIOR = LIST_.back().prior;
        T val = move(MAP_[ID]);
        LIST_.pop_back();
        MAP_.erase(ID);
        MAP_2.erase(ID);
        return make_pair(move(val), move(PRIOR));
  }

private:
    unordered_map<Id, T> MAP_;
    unordered_map<Id, Idd> MAP_2;
    list<Node> LIST_;
    int pos;


};


class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
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
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
   /* PriorityCollection<int> strings;
  const auto white_id = strings.Add(1);
  const auto yellow_id = strings.Add(2);
  const auto red_id = strings.Add(3);
  strings.Promote(yellow_id);
  cout << strings.GetMax().first << strings.GetMax().second << endl;
  strings.Promote(yellow_id);
  cout << strings.GetMax().first << strings.GetMax().second << endl;
  strings.PopMax();
  cout << strings.GetMax().first << strings.GetMax().second << endl;
  strings.PopMax();
  cout << strings.GetMax().first << strings.GetMax().second; */

  return 0;
}
