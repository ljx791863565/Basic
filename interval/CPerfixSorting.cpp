#include <iostream>
#include <assert.h>
class CPrefixSorting
{
public:
	CPrefixSorting()
		:m_nCakeCnt(0), m_nMaxSwap(0);
	{}

	void Run(int *pCakeArray, int nCakeCnt)
	{
		Init(pCakeArray, nCakeCnt);
		m_nSearch = 0;
		Search();
	}
private:
	void Init(int *pCakeArray, int nCakeCnt)
	{
		assert(pCakeArray != NULL);
		assert(nCakeCnt  > 0);

		m_CakeArray = new int[m_nCakeCnt];
		assert(m_CakeArray != NULL);
		for (int i = 0; i < m_nCakeCnt; i++) {
			m_CakeArray[i] = pCakeArray[i];
		}
		m_nMaxSwap = UpBound(m_nCakeCnt);

		m_SwapArray = new int[m_nMaxSwap];
		assert(m_SwapArray != NULL);

		m_ReverseCakeArray = new int[m_nCakeCnt];
		for (int i = 0; i < m_nCakeCnt; i++) {
			m_ReverseCakeArray[i] = m_CakeArray[i];
		}
		m_ReverseCakeArraySwap = new int[m_nMaxSwap];
	}

	int UpBound(int nCakeCnt)
	{
		return nCakeCnt *2;
	}

	void Search(int step)
	{
		
	}

	int *m_CakeArray;
	int m_nCakeCnt;
	int m_nMaxSwap;
	int *m_SwapArray;
	int *m_ReverseCakeArray;
	int *m_ReverseCakeArraySwap;
	int m_nSearch;
};
