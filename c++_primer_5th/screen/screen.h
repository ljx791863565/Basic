#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <iostream>
#include <string>

class Screen
{
public:
	using pos = std::string::size_type;
	Screen() = default;
	Screen(pos ht, pos wd)
		:height(ht), width(wd), contents(ht*wd, ' ')
	{}
	Screen(pos ht, pos wd, char c)
		:height(ht), width(wd), contents(ht*wd, c)
	{}

	char get() const;
	char get(pos r, pos c) const;
	Screen& move(pos r, pos c);
	Screen& set(char ch);
	Screen& set(pos r, pos col, char ch);
	Screen& display(std::ostream &os);
	const Screen& display(std::ostream &os) const;
private:
	pos cursor = 0;
	pos height =0, width = 0;
	std::string contents;
	void do_display(std::ostream &os) const
	{
		os << contents;
	}
};

#endif /* end of :__SCREEN_H__ */
