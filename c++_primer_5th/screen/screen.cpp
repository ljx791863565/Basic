#include "screen.h"

inline char Screen::get() const 
{
	return contents[cursor];
}

inline char Screen::get(pos r, pos col) const
{
	return contents[r*width + col];
}

inline Screen& Screen::move(pos r, pos c)
{
	pos row = r*width;
	cursor = row + c;
	return *this;
}

inline Screen& Screen::set(char ch)
{
	contents[cursor] = ch;
	return *this;
}

inline Screen& Screen::set(pos r, pos c, char ch)
{
	pos row = r *width;
	contents[row + c] = ch;
	return *this;
}

inline Screen& Screen::display(std::ostream &os)
{
	do_display(os);
	return *this;
}

inline const Screen& Screen::display(std::ostream &os) const
{
	do_display(os);
	return *this;
}
