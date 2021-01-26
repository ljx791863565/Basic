#include <iostream>

using namespace std;

class Test
{
public:
	Test(int a)
		:a_(a)
	{
		cout << "Test structure" << endl;
	}
	~Test()
	{
		cout << "Test destructor" << endl;
	}
	Test(const Test &t)
		:a_(t.a_)
	{
		cout << "Test copy structure" << endl;
	}
	Test& operator=(const Test &t)
	{
		if (*this == t)  {
			return *this;
		}
		a_ = t.a_;
		return *this;
	}
	Test &operator+(const Test &lhs, const Test &rhs)
	{
		Test temp;
		temp.a_ = lhs.a_ + rhs.a_;
		return temp;
	}

	Test &operator+=(const Test &rhs)
	{
		this.a_ += rhs.a_;
		return *this;
	}
	bool operator==(const Test &lhs, const Test &rhs)
	{
		return (lhs.a_ == rhs.a_);
	}
	bool operator!=(const Test &lhs, const Test &rhs)
	{
		return !(lhs.a_ == rhs.a_);
	}
	void show()
	{
		cout << "a_ = " << a_ << endl;
	}
private:
	int a_;
};

int main(int argc, const char *argv[])
{
	Test a(2);
	a.show();
	Test b(a);
	b.show();
	Test c = a;
	c.show();
	c += a;
	c.show();
	return 0;
}
