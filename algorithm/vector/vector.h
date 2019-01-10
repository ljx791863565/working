#ifndef __VECTOR__H__
#define __VECTOR__H__

#include <cassert>
#include <cstdlib>
typedef int Rank;
#define DEFAULT_CAPACITY 3
template <typename T>
class Vector
{
protected:
	Rank _size;			//向量实际元素个数
	int _capacity;		//容量
	T *_elem;			//数据区

	void copyFrom(T const* A, Rank lo, Rank hi);		//复制数组区间A[lo, hi)
	void expand();		//空间不足时扩容
	void shrink();		//填装因子过小时压缩
	bool bubble(Rank lo, Rank hi);		//扫描交换
	Rank max(Rank lo, Rank hi);			//选取最大元素
	void bubbleSort(Rank lo, Rank hi);			//冒泡排序
	void selectionSort(Rank lo, Rank hi);		//选择排序
	void merge(Rank lo, Rank mi, Rank hi);		//归并
	void mergeSort(Rank lo, Rank hi);			//归并排序
	Rank partition(Rank lo, Rank hi);			//轴点构造算法
	void quickSort(Rank lo, Rank hi);			//快速排序
	void heapSort(Rank lo, Rank hi);			//堆排序
public:
	Vector(int c = DEFAULT_CAPACITY, int size = s; T v = 0)
	{
		_capacity = c;
		_elem = new T[_capacity];
		
		//s <= c
		for (_size = 0; _size < c; _size++){
			_elem[_size] = v;
		}
	}

	//复制数组区间元素
	Vector(T const *A, Rank lo, Rank hi)
	{
		copyFrom(A, lo, hi);
	}

	//复制整个数组
	Vector(T const *A, Rank n)
	{
		copyFrom(A, 0, n);
	}

	Vector(Vector<T> const &v, Rank lo, Rank hi)
	{
		copyFrom(v._elem, lo, hi);
	}

	Vector(Vector<T> const &v)
	{
		copyFrom(v._elem, 0, v._size);
	}

	~Vector()
	{
		delete [] _elem;
	}

	//仅可读
	Rank size() const
	{
		return _size;
	}

	bool empty() const
	{
		return !_size;
	}

	int disordered() const;		//判断向量是否排序
	Rank find(T const&e, Rank lo, Rank hi) const;		//无序向量区间查找
	//无序向量整体查找
	Rank find(T const&e) const
	{
		return find(e, 0, _size);
	}

	Rank search(T const&e, Rank lo, Rank hi) const;		//有序向量区间查找
	//有序向量整体查找
	Rank search(T const&e) const
	{
		return 0 >= _size ? -1 : search(e, 0, _size);
	}

	//可写
	T& operator[](Rank r) const;			//重载[]运算符
	Vector<T> & operator=(Vector<T> const &);		//重载=运算符
	T remove(Rank r);		//删除r位置元素
	int remove(Rank lo, Rank hi);		//删除[lo, hi)区间的元素,返回值为删除元素个数
	Rank inster(Rank r, T const &e);		//r位置后插入元素e
	//默认在插入在最未
	Rank inster(T const &e)
	{
		return inster(_size, e);
	}

	void sort(Rank lo, Rank hi);		//对[lo, hi)区间排序
	//默认整体排序
	void sort()
	{
		return sort(0, _size);
	}

	void unsort(Rank lo, Rank hi);		//将[lo, hi)顺序打乱
	//默认打乱所有顺序
	void unsort()
	{
		return unsort(0, _size);
	}

	int deduplicate();		//无顺序向量去除重复元素
	int uniquify();			//有序向量去除重复元素

	//便历
	void traverse(void (*)T&);		//遍历。 传入函数指针，只读或局部修改属性
	template <typename VST>
	void traverse(VST &);			//遍历。使用函数对象，可全局修改属性
};
#endif
