#include "list.h"

template <typename T>
inline CSList<T>::CSList() : m_nCount(0), m_pNodeHead(NULL)
{}

template <typename T>
inline CSList<T>::CSList(const T& initdata) : m_nCount(0), m_pNodeHead(NULL)
{
	AddHead(initdata);
}

template <typename T>
inline CSList<T>::~CSList()
{
	RemoveAll();
}

template <typename T>
inline int CSList<T>::IsEmpty() const
{
	return 0 == m_nCount;
}

template <typename T>
inline int CSList<T>::GetCount() const
{
	return m_nCount;
}

template <typename T>
int CSList<T>::AddHead(const T data)
{
	CNode<T> *pNewNode = new CNode<T>;
	if (pNewNode == NULL) {
		return 0;
	}
	pNewNode->data = data;
	pNewNode->next = m_pNodeHead;
	m_pNodeHead = pNewNode;
	++m_nCount;

	return 1;
}

template <typename T>
int CSList<T>::AddTail(const T data)
{
	return InsertAfter(GetCount(), data);
}

template <typename T>
int CSList<T>::InsertBefore(const int pos, const T data)
{
	int nRetPos;
	CNode<T> *pNewNode = new CNode<T>;
	if (pNewNode == NULL) {
		nRetPos = 0;
		return nRetPos;
	}
	pNewNode->data = data;

	if (m_pNodeHead == NULL){
		pNewNode->next = NULL;
		nRetPos = 1;
		m_pNodeHead = pNewNode;
		++m_nCount;
	}

	assert(1 <= pos && pos <= m_nCount);
	if (pos == 1) {
		pNewNode->next = m_pNodeHead;
		m_pNodeHead = pNewNode;
		++m_nCount;
		nRetPos = 1;
	}

	int i = 0;
	CNode<T> *pTmpNode, *pTmpNodePrev;
	pTmpNode = m_pNodeHead;
	for (i = 0; i < pos; i++) {
		pTmpNodePrev = pTmpNode;
		pTmpNode = pTmpNode->next;
	}
	pTmpNodePrev->next = pNewNode;
	pNewNode->next = pTmpNode;
	nRetPos = pos;
	++m_nCount;
	return nRetPos;
}

template <typename T>
int CSList<T>::InsertAfter(const int pos, const T data)
{
	int nRetPos;
	CNode<T> *pNewNode = new CNode<T>;
	if (pNewNode == NULL) {
		nRetPos = 0;
		return nRetPos;
	}
	pNewNode->data = data;
	
	if (m_pNodeHead == NULL){
		pNewNode->next = NULL;
		nRetPos = 1;
		m_pNodeHead = pNewNode;
		++m_nCount;
	}

	assert(1 <= pos && pos <= m_nCount);
	int i = 0;
	CNode<T> *pTmpNode;
	pTmpNode = m_pNodeHead;
	for (i = 0; i < pos; i++) {
		pTmpNode = pTmpNode->next;
	}
	pNewNode->next = pTmpNode->next;
	pTmpNode->next = pNewNode;
	nRetPos = pos+1;
	++m_nCount;
	return nRetPos;
}

template <typename T>
void CSList<T>::RemoveAt(const int pos)
{
	assert(1 <= pos && pos <= m_nCount);
	int i = 0;
	CNode<T> *pTmpNode, *pTmpNodePrev;
	pTmpNode = m_pNodeHead;
	if (pos == 1) {
		m_pNodeHead = NULL;
		delete pTmpNode;
		--m_nCount;
	}

	for (i = 0; i < pos; i++) {
		pTmpNodePrev = pTmpNode;
		pTmpNode = pTmpNode->next;
	}
	pTmpNodePrev->next = pTmpNode->next;
	delete pTmpNode;
	--m_nCount;
}

template <typename T>
void CSList<T>::RemoveHead()
{
	assert(m_nCount != 0);
	RemoveAt(1);
}

template <typename T>
void CSList<T>::RemoveTail()
{
	assert(m_nCount != 0);
	RemoveAt(m_nCount);
}

template <typename T>
void CSList<T>::RemoveAll()
{
	int i;
	CNode<T> *pTmpNode;
	for (i = 0; i < m_nCount; i++) {
		pTmpNode = m_pNodeHead->next;
		delete m_pNodeHead;
		m_pNodeHead = pTmpNode;
	}
	m_nCount = 0;
}

template <typename T>
T& CSList<T>::GetTail()
{
	assert(m_nCount != 0);
	CNode<T> *pTmpNode = m_pNodeHead;
	int i = 0;
	for (i = 0; i < GetCount(); i++) {
		pTmpNode = pTmpNode->next;
	}
	return pTmpNode->data;
}

template <typename T>
T CSList<T>::GetTail() const
{
	assert(m_nCount != 0);
	CNode<T> *pTmpNode = m_pNodeHead;
	int i = 0;
	for (i = 0; i < GetCount(); i++) {
		pTmpNode = pTmpNode->next;
	}
	return pTmpNode->data;
}


template <typename T>
T& CSList<T>::GetHead() 
{
	assert(m_nCount != 0)
	return m_pNodeHead->data;
}

template <typename T>
T CSList<T>::GetHead() const
{
	assert(m_nCount != 0);
	return m_pNodeHead->data;
}

template <typename T>
T& CSList<T>::GetAt(const int pos) 
{
	assert(1 <= pos && pos <= m_nCount);
	CNode<T> *pTmpNode = m_pNodeHead;
	int i = 0;
	for (i = 0; i < pos; i++) {
		pTmpNode = pTmpNode->next;
	}
	return pTmpNode->data;

}

template <typename T>
T CSList<T>::GetAt(const int pos) const
{
	assert(1 <= pos && pos <= m_nCount);
	CNode<T> *pTmpNode = m_pNodeHead;
	int i = 0;
	for (i = 0; i < pos; i++) {
		pTmpNode = pTmpNode->next;
	}
	return pTmpNode->data;
}

template <typename T>
void CSList<T>::SetAt(const int pos, T data)
{
	assert(1 <= pos && pos <= m_nCount);
	CNode<T> *pTmpNode = m_pNodeHead;
	int i = 0;
	for (i = 0; i < pos; i++) {
		pTmpNode = pTmpNode->next;
	}
	pTmpNode->data = data;
}

template <typename T>
int CSList<T>::Find(const T data) const
{
	assert(m_nCount != 0);
	CNode<T> *pTmpNode = m_pNodeHead;
	int i;
	for (i = 0; i < GetCount(); i++) {
		if (data == pTmpNode->data) {
			return i;
		}
		pTmpNode = pTmpNode->next;
	}
}
