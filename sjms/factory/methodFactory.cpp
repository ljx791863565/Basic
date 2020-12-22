#include <iostream>


/*
 * 一个简单的工厂类：一个厂能生产两种核心 定义这两种核心的类代码，定义一个工厂类代码，在工厂类中判断生产哪种核心直接返回该核心的类
 * 这样如果工厂需要增加生产不同的核心只需要添加核心类，在工厂中增加判断，在界面中修改调用，不会涉及到已经有的类的代码
 *
 * 但是问题是如果每次需要修改工厂类就会暴露工厂类的细节，如果我们定义一个方法工厂，将工厂类隐藏起来，暴露其子类给用户
 * 比如建立两个工厂分别生产两种核心，需要生产哪种核心就调用哪个工厂
 * 如果要增加新的产品生产，只需要增加子类工厂
 */
using namespace std;

enum CTYPE{COREA = 0, COREB};

class SingleCore
{
public:
	virtual void show() = 0;
};

class CoreA :public SingleCore
{
public:
	void show()
	{
		cout << "this is coreA" << endl;
		/* do something... */
	}
};

class CoreB :public SingleCore
{
public:
	void show()
	{
		cout << "this is coreB" << endl;
		/* do something... */
	}
};

class Factoey
{
public:
	virtual SingleCore* CreateCore() = 0;
};

class FactoryCoreA
{
public:
	SingleCore* CreateCore()
	{
		return new CoreA();
	}
};

class FactoeyCoreB
{
public:
	SingleCore* CreateCore()
	{
		return new CoreB();
	}
};

int main(int argc, const char *argv[])
{

	//定义生产COREA核心的工厂
	FactoryCoreA fca;
	//定义生产COREB核心的工厂
	FactoeyCoreB fcb;

	//有生产COREA核心的需求 直接访问COREA核心工厂
	SingleCore *sc = fca.CreateCore();
	sc->show();

	//有生产COREA核心的需求 直接访问COREA核心工厂
	sc = fcb.CreateCore();
	sc->show();
	return 0;
}
