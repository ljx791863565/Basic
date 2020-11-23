#ifndef __MEMORY_POOL_H__
#define __MEMORY_POOL_H__
#include <iostream>

typedef unsigned short USHORT;

struct MemoryBlock 
{
	USHORT			nSize;
	USHORT			nFree;
	USHORT			nFirst;
	USHORT			nDummyAlignl;
	MemoryBlock*	pNext;
	char			aData[1];
	static void* operator new(size_t, USHORT nTypes, USHORT nUnitSize)
	{
		return ::operator new(sizeof(MemoryBlock) + nTypes * nUnitSize);
	}
	static void operator delete(void *p, size_t)
	{	
		return ::operator delete(p);
	}
	MemoryBlock(USHORT nType = 1, USHORT nUnitSize = 0);
	~MemoryBlock()
	{
	}

};
class MemoryPool
{
private:
	MemoryBlock*	pBlock;
	USHORT			nUnitSize;
	USHORT			nInitSize;
	USHORT			nGrowSize;
public:
	MemoryPool(USHORT nUnitSize, USHORT nInitSize = 1024, USHORT nGrowSize = 256);
	~MemoryPool();

	void*			Alloc();
	void			Free(void *p);
};
#endif
