#ifndef __MEMORY_POOL_H__
#define __MEMORY_POOL_H__
#include <iostream>

typedef unsigned short USHORT;
typedef unsigned long ULONG;
#define MEMPOOL_ALINGMENT 4
//内存块
struct MemoryBlock 
{
	USHORT			nSize;			//一个内存块的大小 一个内存块可以有几个内存单元
	USHORT			nFree;			//剩下未被分配的内存单元数
	USHORT			nFirst;			//下一个可以被分配的内存单元号
//	USHORT			nDummyAlignl;
	MemoryBlock*	pNext;			//指向下一个内存块地址
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
	MemoryBlock*	pBlock;			//指向第一个MemoryBlock的指针
	USHORT			nUnitSize;		//每个内存单元大小
	USHORT			nInitSize;		//第一个内存块的内存单元数
	USHORT			nGrowSize;		//第一个 block 之外再继续增加的每个 block 的 unit 个数
public:
	MemoryPool(USHORT nUnitSize, USHORT nInitSize = 1024, USHORT nGrowSize = 256);
	~MemoryPool();

	void*			Alloc();
	void			Free(void *p);
};
#endif
