#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <assert.h>

typedef int Rank;	//秩
#define DEFAULT_CAPACITY	3

template <typename T>
class Vector{
protected:
	Rank	_size;		//大小
	int		_capacity;	//容量
	T*		_elem;		//数据域

	void copyFrom(const T *A, Rank lo, Rank hi);	//复制数组区间A[lo, hi)
	void expand();									//空间不足时扩容
	void shrink();									//数据占有率低时压缩空间
	bool bubble(Rank lo, Rank hi);					//扫描交换
	
	Rank max(Rank lo, Rank hi);						//返回[lo, hi)最大元素的Rank
	void bubbleSort(Rank lo, Rank hi);				//冒泡排序算法
	void selectionSort(Rank lo, Rank hi);			//选择排序算法
	void merge(Rank lo, Rank mi, Rank hi);			//归并算法
	void mergeSort(Rank lo, Rank hi);				//归并排序算法
	Rank partition(Rank lo, Rank hi);				//轴点构造算法
	void quickSort(Rank lo, Rank hi);				//快速排序算法
	void heapSort(Rank lo, Rank hi);				//堆排序算法

public:
	//构造函数
	
	//大小为0 容量为DEFAULT_CAPACITY 所有数据初始化为v
	Vector(int c=DEFAULT_CAPACITY, int s=0, T v=0)
	{
		_elem = new T[_capacity=c];
		assert(_elem != nullptr);
		for (_size=0; _size<s; size++) {
			_elem[size] = v;
		}
	}

	//数组整体复制作为初始化
	Vector(const T *A, Rank n)
	{
		copyFrom(A, 0, n);
	}

	//数组区间复制作为初始化
	Vector(const T *A, Rank lo, Rank hi)
	{
		copyFrom(A, lo, hi);
	}

	//向量整体复制初始化
	Vector(const Vector<T> &V)
	{
		copyFrom(V._elem, 0, V._size);
	}

	//向量区间复制初始化
	Vector(const Vector<T> &V, Rank lo, Rank hi)
	{
		copyFrom(V._elem, lo, hi);
	}

	//析构函数
	~Vector()
	{
		delete [] _elem;
	}

	
	//只读访问接口
	Rank size() const
	{
		return _size;
	}

	bool empty() const
	{
		return  !_size;
	}
	
	//判断向量是否有序
	int disordered() const;
	
	//无序向量整体查找e元素 返回找到的最后一个e的Rank 没找到返回-1
	Rank find(const T &e) const
	{
		return find(e, 0, _size);
	}
	//无序向量区间查找
	Rank find(const T &e, Rank lo, Rank hi) const;
	//有序向量整体查找
	Rank search(const T &e) const
	{
		return search(e, 0, _size);
	}
	Rank search(const T &e, Rank lo, Rank hi) const;

	
	//可写访问接口
	
	//下标操作运算符重载
	T& operator[](Rank r) const;
	//赋值运算符重载
	Vector<T>& operator=(const Vector<T> &V);
	//删除秩为r的元素
	T remove(Rank r);
	//删除秩在区间[lo, hi)的全部元素
	int remove(Rank lo, Rank hi);
	//在秩r位置插入元素e
	Rank insert(Rank r, const T &e);
	//在最尾插入元素e
	Rank insert(const T &e)
	{
		insert(_size, e);
	}

	//对区间[lo, hi)排序
	void sort(Rank lo, Rank hi);
	//对向量整体排序
	void sort()
	{
		sort(0, _size);
	}
	//对区间[lo, hi)设置乱序
	void unsort(Rank lo, Rank hi);
	//对向量整体设置乱序
	void unsort()
	{
		unsort(0, _size);
	}

	//无序向量去重
	int deduplicate();
	//有序向量去重
	int uniquify();


	//遍历
	template <typename T>
	void traverse(void (*visit) (T& e));
	
	template <typename T>
	template <typename VST>
	void traverse(VST &);
};

#include "vector_implementation.h"

#endif /* end of :__VECTOR_H__ */
