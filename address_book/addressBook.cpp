#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
using namespace std;

class ShowMenu
{
public:
	void showMenu()
	{
		cout << "****************************" << endl;
		cout << "***	-0- 退出	***" << endl;
		cout << "***	-1- 增加	***" << endl;
		cout << "***	-2- 删除	***" << endl;
		cout << "***	-3- 查看	***" << endl;
		cout << "***	-4- 修改	***" << endl;
		cout << "***	-5- 查看全部	***" << endl;
		cout << "***	-6- 删除全部	***" << endl;
		cout << "****************************" << endl;
	}
};


class Address
{
public:
	Address()
	{}
	Address(const string &name, const string &sex, unsigned int age,
					const string &phone, const string &address)
		:name_(name), sex_(sex), age_(age), phone_(phone), address_(address)
	{
	}
	Address(const Address &a)
	{
		name_ = a.name_;
		sex_ = a.sex_;
		age_ = a.age_;
		phone_ = a.phone_;
		address_ = a.address_;
	}

	Address operator=(const Address &a)
	{
		name_ = a.name_;
		sex_ = a.sex_;
		age_ = a.age_;
		phone_ = a.phone_;
		address_ = a.address_;
		return *this;
	}
	Address set()
	{
		cout << "请输入姓名:" << endl;
		cin >> name_;
		cout << "请输入性别:" << endl;
		cin >> sex_;
		cout << "请输入年龄:" << endl;
		cin >> age_;
		cout << "请输入电话号码:" << endl;
		cin >> phone_;
		cout << "请输入家庭地址:" << endl;
		cin >> address_;

		return *this;
	}
	void display()
	{
		cout << name_ << "\t" << sex_ << "\t" << age_ << "\t" << phone_ << "\t" << address_ << endl;
	}
	
	bool operator==(const Address &rhs) const
	{
		return this->name_ == rhs.name_ 
			&& this->sex_ == rhs.sex_
			&& this->age_ == rhs.age_
			&& this->phone_ == rhs.phone_
			&& this->address_ == rhs.address_;
	}
	friend istream& operator>>(istream &in, string &s)
	{
		in >> s;
		return in;
	}
private:
	string name_;
	string sex_;
	unsigned int age_;
	string phone_;
	string address_;
};

class AddressBook
{
public:
	AddressBook()
	{
		ab_ = new vector<Address>[100];
		count_ = 0;
		size_ = 100;
	}
	~AddressBook()
	{
		count_ = 0;
		size_ = 0;
		delete [] ab_;
	}
	void add(const Address &a)
	{
		if (size_ <= ab_->size())  {
			size_ = size_ *2;
			vector<Address> *temp = new vector<Address>[size_];
			for (auto it = ab_->begin(); it < ab_->end(); ++it) {
				*it = a;
			}
			ab_ = temp;
			delete [] temp;
		}
		ab_->push_back(a);
		count_++;
	}

	void show()
	{
		for (auto it = ab_->begin(); it < ab_->end(); ++it) {
			*it.display();
		}
	}
private:
	vector<Address> *ab_;
	unsigned int count_;
	unsigned int size_;
};
int main(int argc, const char *argv[])
{
	ShowMenu sm;
	int choose = 0;
	Address ad;
	AddressBook ab;
	while (1) {
		sm.showMenu();
		choose = getchar();
		switch (choose)
		{
			system("clean");
			case '1':
				cout << "增加" << endl;
				ad = ad.set();
				ab.add(ad);
				ab.show();
				break;
			case '2':
				cout << "删除" << endl;
				break;
			case '3':
				cout << "查看" << endl;
				break;
			case '4':
				cout << "修改" << endl;
				break;
			case '5':
				cout << "查看全部" << endl;
				break;
			case '6':
				cout << "删除全部" << endl;
				break;
			case '0':
				cout << "退出..." << endl;
				return 0;
			default:
				cout << "输入有误 重新输入" << endl;
		}
		getchar();
	}
	return 0;
}
