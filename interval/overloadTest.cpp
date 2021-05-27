#include <iostream>

class Base
{
public:
	Base()
	{
		std::cout << "this is Base() ..." << std::endl;
	}
	~Base()
	{
		std::cout << "this is ~Base() ..." << std::endl;
	}
	virtual void get(int a)
	{
		std::cout << "this is Base::get(int) " << a << std::endl;
	}
	virtual void set()
	{
		std::cout << "this is Base::set(void) " << std::endl;
	}
};

class Child : public Base 
{
public:
	Child()
	{
		std::cout << "this is Child() ..." << std::endl;
	}
	~Child()
	{
		std::cout << "this is ~Child() ..." << std::endl;
	}
	void get(double d)
	{
		std::cout << "this is Child::get(double) " << d << std::endl;
	}
	void get(int a) override final 
	{
		std::cout << "this is Child::get(int) " << a << std::endl;
	}
	void set() override final
	{
		std::cout << "this is Child::set(void) " << std::endl;
	}
};


int main(int argc, const char *argv[])
{
	Child c;
	c.get(1);
	c.get(1.0);
	c.set();
	
	Base *pb = new Base();
	pb->get(1);
	pb->get(1.0);
	pb->set();
	
	pb = &c;
	pb->get(1);
	pb->get(static_cast<double>(1.0));
	pb->set();
	return 0;
}
