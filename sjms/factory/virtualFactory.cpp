#include <iostream>


/*
 * 
 * 一个简单的工厂类：一个厂能生产两种核心 定义这两种核心的类代码，定义一个工厂类代码，在工厂类中判断生产哪种核心直接返回该核心的类
 * 这样如果工厂需要增加生产不同的核心只需要添加核心类，在工厂中增加判断，在界面中修改调用，不会涉及到已经有的类的代码
 *
 * 但是问题是如果每次需要修改工厂类就会暴露工厂类的细节，如果我们定义一个方法工厂，将工厂类隐藏起来，暴露其子类给用户
 * 比如建立两个工厂分别生产两种核心，需要生产哪种核心就调用哪个工厂
 * 如果要增加新的产品生产，只需要增加子类工厂
 *
 * 虚拟工厂：
 * 上面两种工厂都只能生产单核核心，如果新增需求要求扩增多核心生产线，那么上面的代码都无法使用，现在定义一个虚拟工厂，依然是有多种核心的生产工厂
 * 只是一种工厂需要能生产单核和多核
 * 这时候只暴露了两个生产工厂，如果还需要增加不同类型的核心生产线只需要增加对应的单核或者多核类 并增加对应的生产工厂即可
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

class MultiCore
{
public:
	virtual void MultiShow() = 0;
};

class MultiCoreA :public MultiCore
{
public:
	void MultiShow() 
	{
		cout << "this is MultiCore A" << endl;
		/* do something... */
	}
};
class MultiCoreB :public MultiCore
{
public:
	void MultiShow() 
	{
		cout << "this is MultiCore B" << endl;
		/* do something... */
	}
};
class Factoey
{
public:
	virtual SingleCore* CreateCore() = 0;
	//增加一个工厂对生产多核心的支持
	virtual MultiCore* CreateMultiCore() = 0;
};

class FactoryCoreA
{
public:
	SingleCore* CreateCore()
	{
		return new CoreA();
	}
	MultiCore* CreateMultiCore()
	{
		return new MultiCoreA();
	}
};

class FactoeyCoreB
{
public:
	SingleCore* CreateCore()
	{
		return new CoreB();
	}
	MultiCore* CreateMultiCore()
	{
		return new MultiCoreB();
	}
};

int main(int argc, const char *argv[])
{
	//定义能生产COREA类型核心工厂
	FactoryCoreA fca;
	//定义能生产COREB类型核心工厂
	FactoeyCoreB fcb;

	//有生产COREA类型单核心的需求。直接给到COREA类型工厂
	SingleCore *sc = fca.CreateCore();
	sc->show();
	//有生产COREA类型多核心的需求。也直接给到COREA类型工厂
	MultiCore *mc = fca.CreateMultiCore();
	mc->MultiShow();

	sc = fcb.CreateCore();
	sc->show();
	mc = fca.CreateMultiCore();
	mc->MultiShow();
	return 0;
}
