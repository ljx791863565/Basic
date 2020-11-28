#include "memoryPool.h"
#include <errno.h>
MemoryPool::MemoryPool(USHORT _nUnitSize, USHORT _nInitSize, USHORT _nGrowSize)
{
	pBlock = NULL;
	nInitSize = _nInitSize;
	nGrowSize = _nGrowSize;

	if (_nUnitSize > 4) {
		nUnitSize = (_nUnitSize + (MEMPOOL_ALINGMENT - 1)) & ~(MEMPOOL_ALINGMENT);
	}else if (_nUnitSize <= 2){
		nUnitSize = 2;
	}else {
		nUnitSize = 4;
	}
}

void* MemoryPool::Alloc()
{
	  //第一次调用初始化内存块
	MemoryBlock* pMyBlock = pBlock;
	if (!pBlock) {
		pMyBlock = new(nGrowSize, nUnitSize) MemoryBlock(nGrowSize, nUnitSize);
		pBlock = pMyBlock;
		return (void *)(pMyBlock->aData);
	}
	while (pMyBlock && !pMyBlock->nFree) {
		pMyBlock = pMyBlock->pNext;
	}
	if (pMyBlock) {
		char * pFree = pMyBlock->aData + (pMyBlock->nFirst * nUnitSize);
		//aData记录实际的内存单元标识
		pMyBlock->nFirst = *((USHORT*)pFree);
		pMyBlock->nFree--;
		return (void *)pFree;
	}else {
		if (nGrowSize) {
			return NULL;
		}
		pMyBlock = new(nGrowSize, nUnitSize) MemoryBlock(nGrowSize, nUnitSize);
		if ( !pMyBlock )
			return NULL;

		pMyBlock->pNext = pBlock;
		pBlock = pMyBlock;

		return (void*)(pMyBlock->aData);
	}
}

void MemoryPool::Free( void* pFree )
{
	MemoryBlock* pMyBlock = pBlock;
	MemoryBlock* preMyBlock;
	 //确定该待回收分配单元（pFree）落在哪一个内存块的指针范围内,大于起始节点，小于终止节点。
	while ( ((ULONG)pMyBlock->aData > (ULONG)pFree) ||
			((ULONG)pFree >= ((ULONG)pMyBlock->aData + pMyBlock->nSize)) )
	{
		 //不在内存块范围内，则历遍下一个节点
		preMyBlock = pMyBlock;
		pMyBlock = pMyBlock->pNext;
	}
	pMyBlock->nFree++;                     
	*((USHORT*)pFree) = pMyBlock->nFirst;  
	pMyBlock->nFirst = (USHORT)(((ULONG)pFree-(ULONG)(pBlock->aData)) / nUnitSize);

	 //判断内存块是否全部为自由状态，是则释放整个内存块
	if (pMyBlock->nFree*nUnitSize == pMyBlock->nSize )
	{
		preMyBlock->pNext = pMyBlock->pNext;
		delete pMyBlock;
	}
	else
	{
//		……
	}
}

MemoryBlock::MemoryBlock (USHORT nTypes, USHORT nUnitSize)
	    : nSize(nTypes *nUnitSize), nFree(nTypes - 1), nFirst(1), pNext(0)
{
	char * pData = aData;                  
	for (USHORT i = 1; i < nTypes; i++) 
	{
		//将内存块的前2个字节用来存放内存单元的标识
		*reinterpret_cast<USHORT*>(pData) = i; 
		pData += nUnitSize;
	}
}

MemoryPool::~MemoryPool()
{
    MemoryBlock* pMyBlock = pBlock;
    while (pMyBlock)
    {	
		delete pMyBlock;
		pMyBlock = pMyBlock->pNext;
	}
}


