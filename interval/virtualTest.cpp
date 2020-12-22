#include <iostream>

using namespace std;

class Line
{
public:
	Line(double len)
		:m_len(len)
	{}

	virtual double area() = 0;
	virtual double volume() = 0;
protected:
	double m_len;
};

class Rec : public Line
{
public:
	Rec(double len, double width)
		:Line(len), m_width(width)
	{}
	double area()
	{
		return m_len *m_width;
	}
protected:
	double m_width;
};

class Cuboid : public Rec
{
public:
	Cuboid(double len, double width, double height)
		:Rec(len, width), m_height(height)
	{}
	double area()
	{
		return 2 *(m_len * m_width + m_len * m_height + m_height * m_width);
	}

	double volume()
	{
		return m_len * m_width * m_height;
	}
protected:
	double m_height;
};

class Cube :public Cuboid
{
public:
	Cube(double len)
		:Cuboid(len, len, len)
	{}
	double area()
	{
		return 6*(m_len * m_len);
	}
	double volume()
	{
		return m_len * m_len * m_len;
	}
};


int main(int argc, const char *argv[])
{
	Line *l = new Cuboid(3.14, 2, 3);
	cout << l->area() << endl;
	cout << l->volume() << endl;

	l = new Cube(3);
	cout << l->area() << endl;
	cout << l->volume() << endl;
	return 0;
}
