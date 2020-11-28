#ifndef __STACK_H__
#define __STACK_H__

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10 

template <typename T>
class Stack
{

	Stack()
	{
		base = new T(sizeof(T) * STACK_INIT_SIZE);
		if (base == NULL) {
			exit(0);
		}
		top = base;
		length = STACK_INIT_SIZE;
	}
	~STACK
private:
	T *base;
	T *top;
	int length;
};
#endif //__STACK_H__
