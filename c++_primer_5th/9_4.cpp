#include <iostream>
#include <vector>

using namespace std;

bool Find(vector<int>::iterator begin, vector<int>::iterator end, int e)
{
	while (begin != end) {
		if (*begin == e)  {
			return true;
		}
		++begin;
	}
	return false;
}

int main(int argc, const char *argv[])
{
	std::vector<int> v = {1, 2, 4, 5, 6, 8, 9};
	cout << find(v.begin(), v.end(), 5) << endl;
	cout << find(v.begin(), v.end(), 10) << endl;
	return 0;
}
