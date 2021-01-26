#include <iostream>
#include <string>
#include <vector>

using namespace std;

void display(vector<int* > &a)
{
	for (auto it = a.begin(); it != a.end(); it++) {
		cout << **it << endl;
	}
}

int main(int argc, const char *argv[])
{
	int a = 1; 
	int b = 2;
	int c = 3;
	vector<int *> v = {&a, &b, &c};

	display(v);
	int d = 12;
	v.push_back(&d);
	display(v);


	vector<char> buffer;
	buffer.push_back('h');
	buffer.push_back('e');
	buffer.push_back('l');
	buffer.push_back('l');
	buffer.push_back('o');
	buffer.push_back('w');
	buffer.push_back('o');
	buffer.push_back('e');
	buffer.push_back('l');
	buffer.push_back('d');
	buffer.push_back('!');
	buffer.push_back('\n');
	for (auto it = buffer.begin(); it < buffer.end(); ++it) {
		cout << *it;
	}
	return 0;
}
