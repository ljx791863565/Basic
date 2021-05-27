#ifndef __UNIT_TEST_H__
#define __UNIT_TEST_H__

#include <iostream>
#include <cmath>
#include <vector>

extern int unit_test_failures;

void unittest_fail();

typedef void (*PYSTRINGTestFunc)();

struct PYSTRINGTest
{
	PYSTRINGTestFunc(std::string testgroup, std::string testname, PYSTRINGTestFunc test)
		:group(testgroup), name(testname), function(test)
	{}

	std::string group;
	std::string name;
	PYSTRINGTestFunc function;
};

typedef std::vector<PYSTRINGTest*> UnitTests;

UnitTests& GetUnitTests();

struct AddTest
{
	AddTests(PYSTRINGTest *test);	
};


#define PYSTRING_CHECK_ASSERT(x)									\
	((x) ? ((void)0)												\
		:((std::cout << __FILE__ << ":" << __LINE__ << ":\n"		\
				<< "FAILED: " << #x << "\n"),						\
				(void)++unit_test_failures))						 

#define PYSTRING_CHECK_EQUAL(x, y)									\
	(((x) == (y)) ? ((void)0)										\
		:((std::cout << __FILE__ << ":" << __LINE__ << ":\n"		\
				<< "FAILED: " << #x << " == " << #y <<  "\n"			\
				<< "\tvalues were '" << (x) << "' and '" <<  (y) << "'\n"),\
				(void)++unit_test_failures))						 

#define PYSTRING_CHECK_NE(x, y)									\
	(((x) != (y)) ? ((void)0)										\
		:((std::cout << __FILE__ << ":" << __LINE__ << ":\n"		\
				<< "FAILED: " << #x << " != " << #y <<  "\n"			\
				<< "\tvalues were '" << (x) << "' and '" <<  (y) << "'\n"),\
				(void)++unit_test_failures))						 

#define PYSTRING_CHECK_LT(x, y)									\
	(((x) < (y)) ? ((void)0)										\
		:((std::cout << __FILE__ << ":" << __LINE__ << ":\n"		\
				<< "FAILED: " << #x << " < " << #y <<  "\n"			\
				<< "\tvalues were '" << (x) << "' and '" <<  (y) << "'\n"),\
				(void)++unit_test_failures))						 

#define PYSTRING_CHECK_GT(x, y)									\
	(((x) > (y)) ? ((void)0)										\
		:((std::cout << __FILE__ << ":" << __LINE__ << ":\n"		\
				<< "FAILED: " << #x << " > " << #y <<  "\n"			\
				<< "\tvalues were '" << (x) << "' and '" <<  (y) << "'\n"),\
				(void)++unit_test_failures))						 

#define PYSTRING_CHECK_LE(x, y)									\
	(((x) <= (y)) ? ((void)0)										\
		:((std::cout << __FILE__ << ":" << __LINE__ << ":\n"		\
				<< "FAILED: " << #x << " <= " << #y <<  "\n"			\
				<< "\tvalues were '" << (x) << "' and '" <<  (y) << "'\n"),\
				(void)++unit_test_failures))						 

#define PYSTRING_CHECK_GE(x, y)									\
	(((x) >= (y)) ? ((void)0)										\
		:((std::cout << __FILE__ << ":" << __LINE__ << ":\n"		\
				<< "FAILED: " << #x << " >= " << #y <<  "\n"			\
				<< "\tvalues were '" << (x) << "' and '" <<  (y) << "'\n"),\
				(void)++unit_test_failures))						 

#define PYSTRING_CHECK_CLOSE(x, y, tol)									\
	((std::abs((x)-(y)) < tol) ? ((void)0)										\
		:((std::cout << __FILE__ << ":" << __LINE__ << ":\n"		\
				<< "FAILED: abs(" << #x << " - " << #y << ") < " << #tol <<  "\n"			\
				<< "\tvalues were '" << (x) << "', '" << (y) << "' and '" <<  (tol) << "'\n"),\
				(void)++unit_test_failures))						 

#define PYSTRING_CHECK_THOW(S, E)									\
	try { S; throw "throwanything"; }	catch (E const &ex ){ } catch (...)	{	\
		std::cout << __FILE__ << ":" << __LINE__ << ":\n"		\
				<< "FAILED: " << #E << " is expected to be thrown\n";			\
				(void)++unit_test_failures; }						 
#define PYSTRING_CHECK_THOW(S)									\
	try { S; }	catch (...)	{	\
		std::cout << __FILE__ << ":" << __LINE__ << ":\n"		\
				<< "FAILED: expection thrown from " << #S << "\n";			\
				(void)++unit_test_failures; }				

#define PYSTRING_ADD_TEST(group, name)						\
	static void pystringtest_##group##_##name();			\
	AddTest pystringaddtest_##group##_##name(new PYSTRINGTest(#group, #name, pystringtest_##group##_##name));	\
	static void pystringtest_##group##_##name()

#define PYSTRING_TEST_SETUP()		\
	int unit_test_failures = 0;

#define PYSTRING_TEST_APP(app)		\
	std::vector<PYSTRINGTest*> &GetUnitTests() {	\
		static std::vector<PYSTRINGTest*> pystring_unit_tests;	\
		return pystring_unit_tests;								\
	}															\
	AddTest::AddTest(PYSTRINGTest *test) {						\
		GetUnitTests().push_back(test);							\
	}															\
	PYSTRING_TEST_SETUP();										\
	int main(int, char **) {									\
		std::cerr << "\n" << #app << "\n\n";					\
		for (size_t i = 0; i < GetUnitTests().size(); ++i) {	\
			int _tmp = unit_test_failures;						\
			GetUnitTests()[i]->function();						\
			std::cerr << "Test [" << GetUnitTests()[i]->group << "] [" << GetUnitTests()[i]->name << "] - "; \
			std::cerr << (_tmp == unit_test_failures ? "PASSED" : "FAILED") << "\n";	\
		}														\
		std::cerr << "\n" << unit_test_failures << " tests failed\n";	\
		return unit_test_failures;								\
	}															

#endif //__UNIT_TEST_H__
