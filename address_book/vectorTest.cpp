#include <iostream>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
	vector <int> *p = new vector<int>[5];
	p->push_back(12);
	p->push_back(12);
	p->push_back(12);
	p->push_back(12);

	for (auto it = p->begin(); it < p->end(); ++it) {
		cout << *it << endl;
	}
	delete [] p;
	return 0;
}
