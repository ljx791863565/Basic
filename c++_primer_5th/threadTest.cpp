#include <iostream>
#include <thread>

void func()
{
	std::this_thread::sleep_for(std::chrono::seconds(3));
	std::cout << "this is in thread: time out 3" << std::endl;
}

int main(int argc, const char *argv[])
{
	std::thread t(func);
	std::cout << "thread id: " << t.get_id() << std::endl;

	std::cout << "cpu cour: " << std::thread::hardware_concurrency() << std::endl;
	t.join();
	return 0;
}
