#include <iostream>

class Object
{
public:
	Object()
	{
		std::cout << "this is the Object() " << std::endl;
	}
	Object(int i)
		:n_(i)
	{
		std::cout << "This is the Object(int) " << std::endl;
	}
	Object(const Object &o)
		:n_(o.n_)
	{
		std::cout << "this is the Object(Object &) " << std::endl;
	}

	void add()
	{
		n_ ++;
	}
	
	int getn() const
	{
		return n_;
	}

	void setn(int n)
	{
		n_ = n;
	}
private:
	int n_;
};
int fun(const Object &a)
{
	a.add();
	std::cout << "in the fun " << a.getn() << std::endl;
}

int main(int argc, const char *argv[])
{
	Object a(7);
	fun(a);
//	a.add();
	fun(a);
	a.setn(11);
	fun(a);
	return 0;
}
