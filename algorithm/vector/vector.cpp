#include "vector.h"

template <typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi)
{
	_elem = new T[_capacity = 2 *(hi - lo)];
	_size = 0;
	while (lo < hi){
		_elem[_size++] = A[lo++];
	}
}

template <typename T>
Vector<T>& Vector<T>:: operator=(Vector<T> const &v)
{
	if (_elem){
		delete []_elem;
	}
	copyFrom(v._elem, 0, v.size());
	return *this;
}

template <typename T>
void Vector<T>::expand()
{
	if (_size < _capacity){
		return;
	}

	if (_capacity < DEFAULT_CAPACITY){
		_capacity = DEFAULT_CAPACITY;
	}

	T* oldelem = _elem;
	_elem = new T[_capacity <<= 1];		//加倍扩容
	for (int i = 0; i < _size; i++){
		_elem[i] = oldelem[i];
	}
	delete [] oldelem;
}

template <typename T>
void Vector<T>::shrink()
{
	//不至于压缩到DEFAULT_CAPACITY以下，无需缩容
	if (_capacity < (DEFAULT_CAPACITY << 1)){
		return;
	}

	//以_capacity 1/4容量为标准，空间利用率如达到次标准， 无需缩容
	if (_capacity < _size << 2){
		return;
	}

	T* oldelem = _elem;
	//容量减半
	_elem = new T[_capacity >>= 1];
	for (int i = 0; i < _size; i++){
		_elem[i] = oldelem[i];
	}
	delete [] oldelem;
}

template <typename T>
T& Vector<T>::operator[](Rank r) const
{
	assert(r >= 0 && r < _size);
	return _elem[r];
}

template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{
	//将区间定位到[lo, hi)
	T *v = _elem + lo;	
	for (Rank i = hi - lo; i>0; i--){
		swap(v[i-1], v[rand() % i]);	//v[i-1] 与 v[0, i)随机一个元素互换
	}
}

template <typename T>
Rank Vector<T>::find(T const &e, Rank lo, Rank hi) const
{
	assert(lo >= 0 && lo < hi && hi <= _size);
	//从后向前顺序遍历查找
	//如此当有重复元素时，返回的Rank为其中最大的一个，其余不会做比较
	while (lo < hi--){
		if (e != _elem[hi])
			continue;
		else
			return hi;
	}
		return -1;

	/*
	for (Rank i = hi; i >= lo; i++){
		if (e == _elem[hi]){
			return hi;
		}
	}
	*/
}

template <typename T>
Rank Vector<T>::inster(Rank r, T const &e)
{
	assert(r >= 0 && r <= _size);
	expand();
	//从后向前将位置r以后的元素分别向后移动一个位置
	for (int i = _size; i>r; i++){
		_elem[i] = _elem[i-1];
	}
	_elem[r] = e;
	_size++;
	return r;
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
	assert(lo <= hi);
	if (lo == hi){
		return 0;
	}

	while (hi < _size){
		_elem[lo++] = _elem[hi++];		//[hi, _size) 区间的元素顺序前移 hi-lo个位置
	}
	_size = lo;		//直接将[lo, hi)区间内元素舍弃
	shrink();

	return hi - lo;
}

template <typename T>
T Vector<T>::remove(Rank r)
{
	assert(r >= 0 && r < _size);
	T e = _elem[r];		//备份将被删除元素
	remove(r, r+1);		//即删除r
	return e;			
}

template <typename T>
int Vector<T>::deduplicate()
{
	int oldsize = _size;
	Rank i = 1;
	while (i < _size){
		//如果在[0, i)区间内发现重复的元素，删除它
		if ((find(_elem[i], 0, i)) < 0){
			i++;
		}else{
			remove(i);
		}
	}

	return oldsize - _size;
}

template <typename T>
void Vector<T>::traverse(void (*visit)(T&))
{
	for (int i = 0; i < _size; i++){
		visit(_elem[i]);
	}
}

template <typename T>
template <typename VST>
void Vector<T>::traverse(VST &visit)
{
	for (int i = 0 ; i < _size; i++){
		visit(_elem[i]);
	}
}

//当且仅当 n = 0时向量是有序的， 且为升序
template <typename T>
int Vector<T>::disordered() const
{
	int n = 0;
	for (int i = 1; i < _size; i++){
		if (_elem[i-1] > _elem[i]){
			n++;
		}
		return n;
	}
}


