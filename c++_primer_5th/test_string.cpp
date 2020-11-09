#include <iostream>
#include <string>
using namespace std;
int main(int argc, const char *argv[])
{
	string s("hello world");
	for (auto &c:s) {
		c = toupper(c);
	}	
	cout << s << endl;
	return 0;
}
