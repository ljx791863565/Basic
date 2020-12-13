#include "Timer.h"

using namespace std;
void fun()
{
	for (int i = 0; i < 10000; i++)
		std::cout << "hello world" << std::endl;
}

int main(int argc, const char *argv[])
{
	Timer t;
	fun();
	cout << t.elapsed() << endl;
	cout << t.elapsed_nano() << " ns" << endl;
	cout << t.elapsed_micro() << " us" << endl;
	cout << t.elapsed_seconds() << " s" << endl;
	cout << t.elapsed_minutes() << " min" << endl;
	cout << t.elapsed_hours() << " h" << endl;
	return 0;
}
