/*
 * implicit conversion隐式转换
 * 在C++中有以下情况会出现隐私转换
 *
 * 算术表达式中的转换顺序：
 *   char - int - long - double
 *   flost - double
 *
 * - 在大多数表达是中，比int小的整型数会首先提升为更大的类型
 *   char c = 1;
 *   short s = 2;
 *   int i = c + s; //c提升为short c+s结果赋值给int类型的i
 *   int i1 = i + s;
 * - 在条件语句中， 非bool值转换为bool
 *   int i = 1;
 *   if (i) {
 *		//do something...
 *   }
 *   int *p = &i;
 *   if (p)  {
 *		//do something...
 *   }
 * - 在初始化过程中 初始值转换为变量自身的类型值；赋值语句中等式右边的值转换为左边变量的类型
 *   int ii = 3.14;
 *   double d = 3;
 *   d = ii;
 * - 算术运算或者关系运算中有多种类型的变量， 需要转换为同一种在进行运算
 * - 函数调用发生的类型转换
 */

#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
	//算术类型转换
	
	bool			flag;
	short			sval;
	int				ival;
	long			lval;
	float			fval;
	double			dval;
	char			cval=;
	unsigned short	usval;
	unsigned int	uival;
	unsigned long	ulval;

	3.14159L + 'a';				//转换为long double类型
	dval + ival;				//转换为double类型
	dval + fval;				//转换为double类型
	ival = dval;				//转换为ival类型 损失精度
	flag = dval;				//转换为bool dval为0，flag=false dval不为0，flag=true
	cval + fval;				//转换为float类型
	sval + cval;				//sval和cval都会转换为int类型，然后计算
	cval + lval;				//转换为long类型
	ival + ulval;				//转换为unsigned long类型
	usval + ival;				//根据unsigned short和int类型大小来转换为更大的那一个
	uival + lval;				//根据unsigned int和long类型大小来转换为更大的那一个

	if (fval);					//fval转换为bool类型
	dval = fval + ival;			//ival转换为float类型，计算结果转换为double类型
	dval + ival * cval;			//cval转换为int类型 和ival计算结果转换为double类型和dval计算 最后类型是double
	return 0;
}
