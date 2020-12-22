#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Animal {
public:
	virtual ~Animal()
	{}
	virtual void shout() = 0;

	void setShoutNum(int n)
	{
		shoutNum = n;
	}

	int getShoutNum()
	{
		return shoutNum;
	}

private:
	int shoutNum;
	/* data */
};

class Cat : public Animal
{
public:
	Cat(string s)
		:name(s)
	{
		cout << "i am a cat, my name is " << this->name << endl;
	}
	Cat()
	{
		cout << "i am cat, i don't have a name yet" << endl;
	}
	void shout()
	{
		if (getShoutNum() == 0)  {
			setShoutNum(3);
		}
		for (int i = 0; i < getShoutNum(); i++) {
			cout << "喵 ";
		}
		cout << endl;
	}
private:
	string name;
};
class Dog : public Animal
{
public:
	Dog(string s)
		:name(s)
	{
		cout << "i am a dog, my name is " << this->name << endl;
	}
	Dog()
	{
		cout << "i am dog, i don't have a name yet" << endl;
	}
	void shout()
	{
		if (getShoutNum() == 0)  {
			setShoutNum(2);
		}
		for (int i = 0; i < getShoutNum(); i++) {
			cout << "汪 ";
		}
		cout << endl;
	}
private:
	string name;
};
class Sheep : public Animal
{
public:
	Sheep(string s)
		:name(s)
	{
		cout << "i am a sheep, my name is " << this->name << endl;
	}
	Sheep()
	{
		cout << "i am sheep, i don't have a name yet" << endl;
	}
	void shout()
	{
		if (getShoutNum() == 0)  {
			setShoutNum(3);
		}
		for (int i = 0; i < getShoutNum(); i++) {
			cout << "咩 ";
		}
		cout << endl;
	}
private:
	string name;
};
class Cow : public Animal
{
public:
	Cow(string s)
		:name(s)
	{
		cout << "i am a cow, my name is " << this->name << endl;
	}
	Cow()
	{
		cout << "i am cow, i don't have a name yet" << endl;
	}
	void shout()
	{
		if (getShoutNum() == 0)  {
			setShoutNum(3);
		}
		for (int i = 0; i < getShoutNum(); i++) {
			cout << "哞 ";
		}
		cout << endl;
	}
private:
	string name;
};
class Pig : public Animal
{
public:
	Pig(string s)
		:name(s)
	{
		cout << "i am a pig, my name is " << this->name << endl;
	}
	Pig()
	{
		cout << "i am pig, i don't have a name yet" << endl;
	}
	void shout()
	{
		if (getShoutNum() == 0)  {
			setShoutNum(3);
		}
		for (int i = 0; i < getShoutNum(); i++) {
			cout << "哼 ";
		}
		cout << endl;
	}
private:
	string name;
};

void animal_baoming(vector<Animal *> ai)
{
	cout << "下面进行动物叫声比赛报名..." << endl;
/*
	ai[0] = new Cat("aa");
	ai[1] = new Dog("bb");
	ai[2] = new Sheep("cc");
	ai[3] = new Cow("dd");
	ai[4] = new Pig("ee");
	*/
	ai.push_back(new Cat("aa"));
	ai.push_back(new Dog("bb"));
	ai.push_back(new Sheep("cc"));
	ai.push_back(new Cow("dd"));
	ai.push_back(new Pig("ee"));
}

void animal_jiaoshengbisai(vector<Animal *> ai)
{
	cout << "动物叫声比赛参赛选手依次进行比赛" << endl;
	for (auto it = ai.begin(); it != ai.end(); it++) {
		*it.shout();
	}
}
int main(int argc, const char *argv[])
{
	
//	Cat cat();
//	cat.shout();

//	Cat cat2("mimi");
//	cat2.shout();

	//Animal是一个纯虚类，无法实例化，所以需要使用Animal的指针
	//二级指针是因为数组元素是Animal的指针 数组长度是5
//	Animal *ai[5];

	vector<Animal*> ai;

	/*
	Cat *cat3 = new Cat();
	cat3->shout();

	Cat *cat4 = new Cat("nini");
	cat4->shout();

	ai[0] = cat3;
	ai[0]->shout();

	ai[1] = cat4;
	ai[1]->shout();
	*/
/*
	ai[0] = new Cat("aa");
	ai[1] = new Dog("bb");
	ai[2] = new Sheep("cc");
	ai[3] = new Cow("dd");
	ai[4] = new Pig("ee");
*/
//	animal_baoming(ai);
//	animal_jiaoshengbisai(ai, 5);
	animal_baoming(ai);
	animal_jiaoshengbisai(ai);
	return 0;
}
