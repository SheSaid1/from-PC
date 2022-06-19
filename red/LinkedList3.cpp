#include "test_runner.h"
//#include <vector>
//include <SDL.h>

#include <memory>

using namespace std;



template <typename T>
class LinkedList {
public:
  struct Node {
    T value;
    Node* next = nullptr;

    Node( T data = T(), Node* node = nullptr)  {
        this->value = data;
        this->next = node;
    };

  };
  LinkedList () {
    head = nullptr;
  }

  ~LinkedList() {
    while (head ) {
        Node* tmp = head->next;
        delete head;
        head = tmp;
    }
  }

  void PushFront(const T& Value) {
    if (head == nullptr) {
        head = new Node(Value);
    } else  {
    Node* NewHead = new Node(Value);
    NewHead -> next = head;
    head = NewHead;
     }
  }

  void InsertAfter(Node* node, const T& Value) {
    if (node == nullptr) {
        this->PushFront(Value);

    } else {
        Node* New_next = new Node(Value);
        New_next -> next = node -> next;
        node -> next = New_next;
    }

  }

  void PopFront() {
    if (head == nullptr) {
        return;
    } else {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
  }

  void RemoveAfter(Node* node) {
         if (node == nullptr) {
        this->PopFront();
        return;
    }


    if (node->next == nullptr) {
        return;
    }

        Node* tmp = node->next;
        node->next = tmp->next;
        delete tmp;

  }


  Node* GetHead() { return head; }
  const Node* GetHead() const { return head; }

private:
  Node *head = nullptr;
  //size_t size = 0;
};

template <typename T>
vector<T> ToVector(const LinkedList<T>& list) {
  vector<T> result;
  for (auto node = list.GetHead(); node; node = node->next) {
    result.push_back(node->value);
  }
  return result;
}

void TestPushFront() {
   // cout << endl << "TestPushFront" << endl;

  LinkedList<int> list;

  list.PushFront(1);
  ASSERT_EQUAL(list.GetHead()->value, 1);
  list.PushFront(2);
  ASSERT_EQUAL(list.GetHead()->value, 2);
  list.PushFront(3);
  ASSERT_EQUAL(list.GetHead()->value, 3);

  const vector<int> expected = {3, 2, 1};
  ASSERT_EQUAL(ToVector(list), expected);
}

void TestInsertAfter() {
  //  cout << endl << "TestInsertAfter" << endl;

  LinkedList<string> list;

  list.PushFront("a");
  auto head = list.GetHead();
  ASSERT(head);
  ASSERT_EQUAL(head->value, "a");

  list.InsertAfter(head, "b");
  const vector<string> expected1 = {"a", "b"};
  ASSERT_EQUAL(ToVector(list), expected1);

  list.InsertAfter(head, "c");
  const vector<string> expected2 = {"a", "c", "b"};
  ASSERT_EQUAL(ToVector(list), expected2);
}

void TestRemoveAfter() {
   // cout << endl << "TestRemoveAfter" << endl;

  LinkedList<int> list;
  for (int i = 1; i <= 5; ++i) {
    list.PushFront(i);
  }

  const vector<int> expected = {5, 4, 3, 2, 1};
  ASSERT_EQUAL(ToVector(list), expected);

  auto next_to_head = list.GetHead()->next;
  list.RemoveAfter(next_to_head);
  list.RemoveAfter(next_to_head);

  const vector<int> expected1 = {5, 4, 1};
  ASSERT_EQUAL(ToVector(list), expected1);

  while (list.GetHead()->next) {
    list.RemoveAfter(list.GetHead());
  }
  ASSERT_EQUAL(list.GetHead()->value, 5);
}

void TestPopFront() {
    //cout << endl << "TestPopFront" << endl;
  LinkedList<int> list;

  for (int i = 1; i <= 5; ++i) {
    list.PushFront(i);
  }
  for (int i = 1; i <= 5; ++i) {
    list.PopFront();
  }
  ASSERT(list.GetHead() == nullptr);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestPushFront);
  RUN_TEST(tr, TestInsertAfter);
  RUN_TEST(tr, TestRemoveAfter);
  RUN_TEST(tr, TestPopFront);


  return 0;
}

