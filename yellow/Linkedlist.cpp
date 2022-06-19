#include <iostream>
#include <cstdlib>
using namespace std;

class Node
{
public :
    Node* next;
    int data;

};


class LinkedList
{
public:
    int length;
    Node* head;
    LinkedList();
    ~LinkedList();
    void add(int data);
    void del (int data);
    void print();

};
LinkedList::LinkedList()
{
    this->length=0;
    this->head=NULL;

}
void LinkedList:: del(int data){


}
LinkedList::~LinkedList(){
    std::cout << "LIST DELETED";
}
void LinkedList::add(int data){
    Node* node= new Node();
    node->data=data;
    node->next=this->head;
    this->head=node;
    this->length++;
}

void LinkedList::print(){
    Node* head = this->head;
    int i = 1;
    while(head){
        std::cout << i << ": " << head->data << std::endl;
        head = head->next;
        i++;
    }
}

int main()
{
    LinkedList* list1 = new LinkedList();
    for (int i = 0; i < 100; ++i)
    {
        list1->add(rand() % 100);
    }
    list1->print();
    cout << "List Length: " << list1->length << endl;
    delete list1;
    return 0;
}
