//nasledovanie.cp
#include <iostream>
#include <string>
using namespace std;

/*
struct Fruit {
    int health =0;
    string type ="fruit";
};


struct Apple : public Fruit
{
    Apple() {
    health=10;
    type = "apple";
    }
};

struct Orange : public Fruit { // ��� ��������� ������������ : public Fruit
Orange () { // ��� ��� �� ����������
health = 5;
type = "orange";
 }
};


class Animal{
public :
    void Eat(const Fruit& f)
    {
        cout<<type << " eats" <<f.type<< "." <<f.health;
    }
    string type = "animal";
};
class Cat : public Animal
{
public :
    Cat()
    {
        type = "cat";
    }
    void Meow() const
    {
        cout<<"meow";
    }

};
class Dog : public Animal
{
public :
    Dog()
    {
        type = "dog";
    }


};


void DoMeal(Animal& a, Fruit& f) {
a.Eat(f);
}

 */
 class Animal {
public:
    // ��� ���
    Animal (const string &s) : Name(s)
    {

    }

    const string Name;
};


class Dog : public Animal  {
public:
    // ��� ���
    Dog(const string &s) : Animal(s)
    {

    }

    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};



int main()

{

    return 0;
}
