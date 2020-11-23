#include "memoryPool.h"
#include <errno.h>
MemoryPool::MemoryPool(USHORT _nUnitSize, USHORT _nInitSize, USHORT _nGrowSize)
{
	pBlock = NULL;
	nInitSize = _nInitSize;
	nGrewSize = _nGrewSize;

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
	if (!pBlock) {
		
	}
}
