#include "vector.h"
#include "vector_implementation.h"

template <typename T>
T& Vector<T>::operator[](Rank r) const
{
	return _elem[r];
}

template <typename T>
void Vector<T>::copyFrom(const T *A, Rank lo, Rank hi)
{
	_elem = new T[_capacity = 2*(hi-lo)];
	assert(_elem != nullptr);
	_size = 0;
	while (lo < hi) {
		_elem[_size++] = A[lo++];
	}
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> &V)
{
	if (_elem)  {
		delete [] _elem;
	}
	copyFrom(V._elem, 0, V.size());
	return *this;
}

template <typename T>
void Vector<T>::expand()
{
	if (_size < _capacity)  {
		return;
	}
	if (_capacity < DEFAULT_CAPACITY)  {
		_capacity = DEFAULT_CAPACITY;
	}
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];
	assert(_elem != nullptr);
	for (int i = 0; i < _size; i++) {
		_elem[i] = oldElem[i];
	}
	delete [] oldElem;
}

template <typename T>
void Vector<T>::shrink()
{
	if (_capacity < (DEFAULT_CAPACITY << 1))  {
		return;
	}
	//确保_size降低到_capacity的1/4时才开始收缩
	if ((_size << 2) > _capacity)  {
		return;
	}
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];
	assert(_elem != nullptr);
	for (int i = 0; i < _size; i++) {
		_elem[i] = oleElem[i];
	}
	delete []  oldElem;
}

template <typename T>
Rank Vector<T>::insert(Rank r, const T &e)
{
	//每一个插入动作之前都需要检查扩容状态
	expand();
	for (int i = _size; i > r ; i--) {
		_elem[i] = _elem[i-1];
	}
	_elem[r] = e;
	_size++;
	return r;
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
	if (lo == hi)  {
		return 0;
	}
	while (hi < _size) {
		//从lo开始顺序迁移hi-lo个单位 直到_size位置
		_elem[lo++] = _elem[hi++];
	}
	_size = lo;	//此时lo记为所有元素的数量
	shrink();
	return hi - lo;
}

template <typename T>
T Vector<T>::remove(Rank r)
{
	assert(r >=0 && r <= _size);
	T e = _elem[r];
	remove(r, r+1);
	return e;
}

template <typename T>
int Vector<T>::disordered() const
{
	int n = 0;
	for (int i = 1; i < _size; i++) {
		if (_elem[i-1] > _elem[i])  {
			n++;
		}
	}
	//当且仅当n=0时向量有序
	return n;
}

template <typename T>
Rank Vector<T>::find(const T &e, Rank lo, Rank hi) const
{
	while ((lo < hi--) && (e != _elem[hi])) {
		return hi;
	}	
}

template <typename T>
static Rank binSearch(T *A, const T &e, Rank lo, Rank hi)
{
	while (lo < hi) {
		Rank mi = (lo + hi) >> 1;
		if (e < A[mi])  {
			hi = mi;
		}else if (e > A[mi]) {
			lo = mi+1;
		}else {
			return mi;
		}
	}
	return -1;
}

#include "../fibonacci/Fib.h"
template <typename T>
static Rank fibSearch(T *A, const T &e, Rank lo, Rank hi)
{
	Fib fib(hi-lo);
	while (lo < hi) {
		while ((hi - lo) < fib.get()) {
			fib.prev();
			Rank mi = lo + fib.get() -1;
			if (e < A[mi])  {
				hi = mi;
			}else if (e > A[mi]) {
				lo = mi+1;
			}else {
				return mi;
			}
		}
	}
	return -1;
}

template <typename T>
Rank Vector<T>::search(const T &e, Rank lo, Rank hi) const
{
	return (rand() %2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}

template <typename T>
void Vector<T>::traverse(void (*visit) (T&))
{
	for (int i = 0; i < _size; i++) {
		visit(_elem[i]);
	}
}

template <typename T>
template <typename VST>
void Vector<T>::traverse(VST &visit)
{
	for (int i = 0; i < _size; i++) {
		visit(_elem[i]);
	}
}

template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{
	T *v = _elem + lo;
	for (Rank i = hi-lo; i > 0; i--) {
		swap(V[i-1], V[rand()%i]);
	}
}

template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi)
{
	bool sorted = true;
	while (++lo < hi) {
		if (_elem[lo - 1] > _elem[lo])  {
			sorted = false;
			swap(_elem[lo-1], _elem[lo]);
		}
	}
	return sorted;
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
	while (!bubble(lo, hi--)) {
		NULL;
	}
}

template <typename T>
Rank Vector<T>::max(Rank lo, Rank hi)
{
	Rank mx = hi;
	while (lo < hi--) {
		if (_elem[hi] > _elem[mx])  {
			mx = hi;
		}
	}
	return mx;
}

template <typename T>
void Vector<T>::selectSort(Rank lo, Rank hi)
{
	while (lo < --hi) {
		swap(_elem[max(lo, hi)], _elem[hi]);
	}
}

template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
	T *A = _elem + lo;
	int lb = mi - lo;

	T *B = new T[lb];
	assert(B != nullptr);
	for (Rank i = 0; i < lb;) {
		B[i] = A[i++];
	}

	int lc = hi -mi;
	T *C = _elem + mi;
	for (Rank i=0, j=0, k=0; (j<lb)||(k<lc); ) {
		if ((j<lb) && (!(k<lc) || (B[j] <= C[k])))  {
			A[i++] = B[j++];
		}
		if ((k<lc) && (!(j<lb) || (C[k] < B[j])))  {
			A[i++] = C[k++];
		}
	}
	delete [] B;
}

template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if ((hi-lo) < 2)  {
		return;
	}
	int mi = (lo+hi)/2;
	mergeSort(lo, mi);
	mergeSort(mi, hi);
	merge(lo, mi, hi);
}
	
template <typename T>
void Vector<T>::quickSort(Rank lo, Rank hi)
{
	if ((hi-lo) < 2)  {
		return;
	}
	Rank mi = partition(lo, hi - 1);
	quickSort(lo, mi);
	quickSort(mi+1, hi);
}

template <typename T>
void Vector<T>::heapSort(Rank lo, Rank hi)
{
	//fixme
}

template <typename T>
void Vevtor<T>::sort(Rank lo, Rank hi)
{
	switch(rand() % 5)
	{
		case 1:
			bubuleSort(lo, hi);
			break;
		case 2:
			selectionSort(lo, hi);
			break;
		case 3:
			mergeSort(lo, hi);
			break;
		case 4:
			heapSort(lo, hi);
			break;
		default:
			quickSort(lo, hi);
			break;
	}
}

template <typename T>
Rank Vector<T>::partition(Rank lo, Rank hi)
{
	swap(_elem[lo], _elem[lo + rand() %(hi-lo+1)]);
	T pivot = _elem[lo];
	while (lo < hi) {
		while (lo < hi) {
			if (pivot < _elem[hi])  {
				hi--;
			}else {
				_elem[lo++] = _elem[hi];
				break;
			}
		}
		while (lo < hi) {
			if (_elem[lo] < pivot)  {
				lo++;
			}else {
				_elem[hi--] = _elem[lo];
				break;
			}
		}
	}
	_elem[lo] = pivot;
	return lo;
}

template <typename T>
int Vector<T>::uniquify()
{
	Rank i = 0;
	Rank j = 0;
	while (++j < _size) {
		if (_elem[i] != _elem[j])  {
			_elem[++i] = _elem[j];
		}
	}
	_size = ++i;
	shrink();
	return j-i;
}

template <typename T>
int Vector<T>::deduplicate()
{
	int oldSize = _size;
	Rank i = 1;
	while (i < _size) {
		(find(_elem[i], 0, i) < 0)? 
			i++ : remove(i);
	}
	return oldSize - _size;
}
