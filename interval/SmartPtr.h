#include <iostream>

class Point
{
public:
	Point(int xval, int yval)
		:x(xcal), y(yval)
	{}
	int getx(void) const 
	{
		return x;
	}

	int gety(void) const 
	{
		return y;
	}

	void setx(int xval)
	{
		x = xval;
	}

	void sety(int yval)
	{
		y = yval;
	}
private:
	int x;
	int y;
};

class RefPtr
{
	friend class SmartPtr;
	RefPtr(Point *ptr)
		:p_(ptr), count_(1)
	{}

	~RefPtr()
	{
		delete p_;
	}

	Point *p_;
	int count;
};

class SmartPtr 
{
public:
	SmartPtr(Point *ptr)
		:rp (new RefPtr(ptr))
	{}

	SmartPtr(const SmartPtr &sp)
		:rp(sp.rp)
	{
		++rp->count;
	}

	SmartPtr& operator=(const SmartPtr &rhs)
	{
		++rhs.rp->count;
		if (--rp->count == 0)  {
			delete rp;
		}
		rp = rhs.rp;
		return *this;
	}

	~SmartPtr()
	{
		if (--rp->count == 0)  {
			delete rp;
		}
	}
private:
	RefPtr *rp;
};

