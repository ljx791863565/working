#include "listNode.h"

template <typename T>
class List
{
private:
	int _size;
	ListNodePosi(T) header;			//头指针
	ListNodePosi(T) trailer;		//尾指针

protected:
	void init();		//列表初始化
	int clear();		//清除所有节点
	void copyNodes(ListNodePosi(T) p, int n);		//复制列表自p起n项
	void merge(ListNodePosi(T) &l1, int m, List<T> &L, ListNodePosi(T) l2, int n);	//有序列表l1, l2归并
	void mergeSort(ListNodePosi(T) &p, int n);		//对从p开始对n个节点归并并排序
	void selectionSort(ListNodePosi(T) p, int n);	//对从p开始n个几点选择排序
	void insertionSort(ListNodePosi(T) p, int n);	//对从p开始n个节点插入排序
public:
	List()
	{
		init();
	}
	List(List<T> const &L);		//复制列表L
	List(List<T> const &L, Rank r, Rank n);			//复制列表L的第r项到第n项
	List(ListNodePosi(T) p, int n);					//复制列比中第p位置起的n项
	~List()
	{

	}

//只读接口
	Rank size() const
	{
		return _size;
	}

	bool empty() const
	{
		return _size<=0;
	}

	T& operator[](Rank r) const;
	
	//首节点位置
	ListNodePosi(T)& first() const
	{
		return header->succ;
	}

	//尾节点位置
	ListNodePosi(T)& last() const
	{
		return trailer->pred;
	}
	
	//判断p是否对外合法
	bool valid(ListNodePosi(T) p) const
	{
		return p && (header != p) && (trailer != p);
	}

	//判断列表是否有序
	int disordered() const;
	
	ListNodePosi(T) find(T const &e) const		//无序列表查找
	{
		return find(e, _size, trailer);
	}
	ListNodePosi(T) find(T const &e, int n, ListNodePosi(T) p) const;		//无序区间查找	
	
	ListNodePosi(T) search(T const &e) const		//有序列表查找
	{
		return search(e, _size, trailer);
	}
	ListNodePosi(T) search(T const &e, int n, ListNodePosi(T) p) const;		//有序区间查找

	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n) const;			//在p及其前n-1个后继中找出最大者

	ListNodePosi(T) selectMax() const			//整个列表的最大者
	{		
		return selectMax(header->succ, _size);
	}

//可写接口
	ListNodePosi(T) insertAsFirst(T const &e);		//将e作为首节点插入
	ListNodePosi(T) insertAsLast(T const &e);		//将e作为末节点插入
	ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const &e);		//将e作为p位置前驱插入
	ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const &e);			//将e作为p位置后继插入
	T remove(ListNodePosi(T) p);		//删除合法位置p处节点，并返回被删除节点
	
	//全列表归并
	void merge(List<T> &L)
	{
		return merge(first(), size, L, L.first(), L._size);
	}

	void sort(ListNodePosi(T) p, int n);

	void sort()
	{
		return sort(first(), _size);
	}

	int dedupilcate();		//无序去重
	int uniquify();			//有序去重

	void reverse();			//前后倒置

//遍历
	void traverse(void (*)(T&));
	template <typename VST>
	void traverse(VST&);
};
