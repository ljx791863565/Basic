#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

int main(int argc, const char *argv[])
{
	//以这种方式声明的shared_ptr会在最后一个拥有者被销毁时调用这个lambda表达式
	shared_ptr<string> pNico(new string("nico"), [](string *p){
													cout << "delete" << *p << endl; 
													delete p;
													});
	shared_ptr<string> pJutta(new string("jutta"));

	(*pNico)[0] = 'N';
	pJutta->replace(0, 1, "J");

	vector<shared_ptr<string>> whoMadeCoffee;
	whoMadeCoffee.push_back(pJutta);
	whoMadeCoffee.push_back(pJutta);
	whoMadeCoffee.push_back(pNico);
	whoMadeCoffee.push_back(pJutta);
	whoMadeCoffee.push_back(pNico);
	whoMadeCoffee.push_back(pJutta);

	for (auto ptr : whoMadeCoffee) {
		cout << *ptr << " ";
	}
	cout << endl;

	*pNico = "Nicoai";

	for (auto ptr : whoMadeCoffee) {
		cout << *ptr << " ";
	}
	cout << endl;

	//这里表示某个shared_ptr当前指向某地址数量 
	//输出5 指向"Jutta" 在whoMadeCoffee中有四个copy 在定义时有一个
	cout << "use_count: " << whoMadeCoffee[1].use_count() << endl; 

	pNico = nullptr;
	whoMadeCoffee.resize(3);
	return 0;
}
