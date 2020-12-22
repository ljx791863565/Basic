#include <iostream>


/*
 * 一个简单的工厂类：一个厂能生产两种核心 定义这两种核心的类代码，定义一个工厂类代码，在工厂类中判断生产哪种核心直接返回该核心的类
 * 这样如果工厂需要增加生产不同的核心只需要添加核心类，在工厂中增加判断，在界面中修改调用，不会涉及到已经有的类的代码
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

class CoreFactory
{
public:
	SingleCore* CreateCore(enum CTYPE ctype)
	{
	
		switch(ctype)
		{
			case COREA:
				return new CoreA();
			case COREB:
				return new CoreB();
			default:
				return NULL;
		}
	}
};

int main(int argc, const char *argv[])
{
	//实例一个工厂
	CoreFactory cf;
	//向工厂提供生产COREA类核心的需求
	SingleCore *sc = cf.CreateCore(COREA);
	//生产COREA类核心
	sc->show();


	sc = cf.CreateCore(COREB);
	sc->show();
	return 0;
}
