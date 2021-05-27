#include <iostream>
#include <string>
#include <vector>
// 必须先定义Window_mamager类，再声明函数clean且不定义， 定义Screen类声明函数clean是该类友元函数 
// 最后定义clean函数 
class Window_manager 
{
public:
	void clean();
};

class Screen
{
public:
	friend void Window_manager::clean();

	using pos = std::string::size_type;

	Screen() = default;
	Screen(pos ht, pos wd)
		:height(ht), width(wd), contents(ht * wd, ' ')
	{}

	Screen(pos ht, pos wd, char c)
		:height(ht), width(wd), contents(ht * wd, c)
	{}

	char get() const 
	{
		return contents[cursor];
	}

	char get(pos row, pos col) const 
	{
		return contents[row*col + col];
	}

	Screen &set(char c)
	{
		contents[cursor] = c;
		return *this;
	}

	Screen &set(pos row, pos col, char c)
	{
		contents[row*width + col] = c;
		return *this;
	}

	Screen &move(pos row, pos col)
	{
		pos r = row * width;
		cursor = r + col;
		return *this;
	}

	Screen &display(std::ostream &os)
	{
		do_display(os);
		return *this;
	}

	const Screen &display(std::ostream &os) const 
	{
		do_display(os);
		return *this;
	}

private:
	void do_display(std::ostream &os) const 
	{
		os << contents;
	}

private:
	std::string contents;
	pos height = 0, width = 0;
	pos cursor = 0;
};


void Window_manager::clean()
{
	Screen myScreen(5, 4, '*');
	myScreen.display(std::cout);
	std::cout << std::endl;
	std::cout << "be clean..." << std::endl;
	std::cout << std::endl;
	myScreen.contents = "";
	std::cout << std::endl;
	myScreen.display(std::cout);
}

int main(int argc, const char *argv[])
{
	Screen myScreen(5, 5, 'x');
	myScreen.display(std::cout);
	std::cout << std::endl;
	
	myScreen.move(4, 0).set('#').display(std::cout);
	std::cout << std::endl;

	
	const Screen myScreen2(5, 5, 'c');
	myScreen2.display(std::cout);
	std::cout << std::endl;

	Window_manager w;
	w.clean();
	return 0;
}
