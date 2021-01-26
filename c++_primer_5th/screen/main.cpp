#include "screen.h"
//#include "screen.cpp"
using namespace std;
int main(int argc, const char *argv[])
{
	Screen myScreen(5, 3);
	const Screen blank(5, 3);
	myScreen.move(4, 0).set('#').display(cout);
	cout << "\n";
	blank.display(cout);
	cout << "\n";
	return 0;
}
