#ifndef __LIST_H__
#define __LIST_H__

#include <iostream>
#include <cstdio>
#include <cassert>

template <typename T>
class CNode
{
public:
	CNode() :data(0) , next(NULL){}
	
	CNode(const T &initdata, CNode<T> *p) :data(initdata), next(p){}

	~CNode()
	{
		data = 0;
		next = NULL;
	}

public:
	T data;						//数据域
	CNode<T> *next;				//指针域
};

template <typename T>
class CSList
{
public:
	CSList();
	CSList(const T &initdata);
	~CSList();

public:
	int		IsEmpty() const;
	int		GetCount() const;
	int		InsertBefore(const int pos, const T data);
	int		InsertAfter(const int pos, const T data);
	int		AddHead(const T data);
	int		AddTail(const T data);
	void	RemoveHead();
	void	RemoveTail();
	void	RemoveAll();
	void	RemoveAt(const int pos);
	T&		GetTail();
	T		GetTail() const;
	T&		GrtHead();
	T		GetHead() const;
	T&		GetAt(const int pos);
	T		GetAt(const int pos) const;
	void	SetAt(const int pos, T data);
	int		Find(const T data) const;
protected:
	int m_nCount;				//节点个数
	CNode<T> *m_pNodeHead;		//头结点指针
};
#endif //__LIST_H__
