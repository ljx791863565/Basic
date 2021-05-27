#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Animal
{
public:
	virtual void getShoutSound();
	int shoutNum = 3;
	void setShoutNum(int n)
	{
		shoutNum = n;
	}
	int getShoutNum() const 
	{
		return shoutNum;
	}
};

class Cat : public Animal 
{
public:
	Cat(string s)
		:name_(s)
	{
		cout << "i am cat, my name is " << name_ << endl;
	}
	Cat()
	{
		cout << "i am cat, i have no name" << endl;
	}
	void getShoutSound()
	{
		for (int i = 0; i < shoutNum; i++) {
			cout << "喵 ";
		}
		cout << endl;
	}
private:
	string name_;
};

class Dog : public Animal 
{
public:
	Dog(string s)
		:name_(s)
	{
		cout << "i am dog, my name is " << name_ << endl;
	}
	Dog()
	{
		cout << "i am dog, i have no name" << endl;
	}
	void getShoutSound()
	{
		for (int i = 0; i < shoutNum; i++) {
			cout << "汪 ";
		}
		cout << endl;
	}
private:
	string name_;
};
class Cattle : public Animal 
{
public:
	Cattle(string s)
		:name_(s)
	{
		cout << "i am cattle, my name is " << name_ << endl;
	}
	Cattle()
	{
		cout << "i am cattle, i have no name" << endl;
	}
	void getShoutSound()
	{
		for (int i = 0; i < shoutNum; i++) {
			cout << "哞 ";
		}
		cout << endl;
	}
private:
	string name_;
};
class Sheep : public Animal 
{
public:
	Sheep(string s)
		:name_(s)
	{
		cout << "i am sheep, my name is " << name_ << endl;
	}
	Sheep()
	{
		cout << "i am sheep, i have no name" << endl;
	}
	void getShoutSound()
	{
		for (int i = 0; i < shoutNum; i++) {
			cout << "咩 ";
		}
		cout << endl;
	}
private:
	string name_;
};
int main()
{
	Cat cat("咪咪");
	cat.getShoutSound();

	Animal *animal = new Animal[5];
	animal[0] = Cat cat("mimi");
	animal[1] = Dog("taidi");
	animal[2] = Cattle("xiaohua");
	animal[3] = Sheep("xiaohei");
	animal[4] = Cat("buou");

	for (int i = 0; i < 5; i++) {
		animal[i],getShoutSound();
	}
}


