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
	return 0;
}
