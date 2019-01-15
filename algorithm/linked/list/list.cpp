#include "list.h"

template <typename T>
void List<T>::init()
{
	header = new ListNode<T>;
	trailer = new ListNode<T>;

	header->succ = trailer;
	header->pred = NULL;
	trailer->pred = header;
	trailer->succ = NULL;

	_size = 0;
}

//效率低
template  <typename T>
T& List<T>::operator[](Rank r) const
{
	assert(r >=0 && r <= _size);
	ListNodePosi(T) p = first();
	while (0 < r--){
		p = p->succ;
	}
	return p->data;
}

template  <typename T>
ListNodePosi(T) List<T>::find(T const &e, int n, ListNodePosi(T) p) const
{
	//自右向左遍历p的n个前驱
	while (n-- > 0){
		if (e == (p = p->pred)->data){
			return p;
		}
	}
	return NULL;
}

template  <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const &e)
{
	ListNodePosi(T) x = new ListNode(e, pred, this);
	pred->succ = x;
	pred = x;
	return x;
}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const &e)
{
	ListNodePosi(T) x = new ListNode(e, this, succ);
	succ->pred = x;
	succ = x;
	return x;
}
template  <typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const &e)
{
	_size++;
	return header->insertAsSucc(e);
}

template  <typename T>
ListNodePosi(T) List<T>::insertAsLast(T const &e)
{
	_size++;
	return trailer->insertAsPred(e);
}

template  <typename T>
ListNodePosi(T) List<T>::insertBefore(ListNodePosi(T) p, T const &e)
{
	_size++;
	return p->insertAsPred(e);
}

template  <typename T>
ListNodePosi(T) List<T>::insertAfter(ListNodePosi(T) p, T const &e)
{
	_size++;
	return p->insertAsSucc(e);
}

void List<T>::copyNodes(ListNodePosi(T) p, int n)
{
	init();
	while (n--){
		insertAsLast(p->data);
		p = p->succ;
	}
}

template <typename T>
List<T>::List(List<T> const &L)
{
	copyNodes(L.first(), L._size);
}

template <typename T>
List<T>::List(List<T> const &L, Rank r, Rank n)
{
	copyNodes(L[r], n);
}

template <typename T>
List<T>::List(ListNodePosi(T) p, int n)
{
	copyNodes(p, n);
}

template <typename T>
T List<T>::remove(ListNodePosi(T) p)
{
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return e;
}

template <typename T>
List<T>::~List()
{
	clear();
	delete header;
	delete trailer;
}

template <typename T>
int List<T>::clear()
{
	int oldsize = _size;
	while (_size > 0){
		remove(hearer->succ);
	}
	return oldsize;
}

//返回值为被删除的重复元素的总数
template <typename T>
int List<T>::dedupilcate()
{
	if (_size < 2){
		return 0;
	}
	int oldsize = _size;
	ListNodePosi(T) p = header;
	Rank r = 0;
	while ((p = p->succ) != trailer){
		ListNodePosi(T) q = find(p->data, r, p);
		q ? remove(q) : r++;
	} 
	return oldsize - _size;

}

template <typename T>
void List<T>::traverse(void (*visit)(T&))
{
	for (ListNodePosi(T) p = header; p != trailer; p = p->succ){
		visit(p->data);
	}
}

template <typename VST>
template <typename T>
void List<T>::traverse(VST& visit)
{
	for (ListNodePosi(T) p = header; p != trailer; p = p->succ){
		visit(p->data);
	}
}

template <typename T>
int List<T>::uniquify()
{
	if (_size < 2){
		return 0;
	}
	int oldsize = _size;
	ListNodePosi(T) p = header;
	ListNodePosi(T) q = p->succ;
	for (; q != trailer; p = q, q = q->succ){
		if (p->data == q->data){
			remove(q);
			q = p;
		}
	}
	return oldsize - _size;
}

template <typename T>
ListNodePosi(T) List<T>::search(T const &e, int n, ListNodePosi(T) p) const
{
	while (n-- >= 0){
		if ((p = p->succ)->data <= e){
			break;
		}
	}
	return p;
}

template <typename T>
void List<T>::sort(ListNodePosi(T) p, int n)
{
	switch(rank() % 3)
	{
		case 1:
			selectionSort(p, n);
			break;
		case 2:
			insertionSort(p, n);
			break;
		default:
			mergeSort(p, n);
			break;
	}
}

template <typename T>
void insertionSort(ListNodePosi(T) p, int n)
{
	for (int r = 0; r < n; r++){
		insertAfter(search(p->data, r, p), p->data);
		p = p->succ;
		remove(p);
	}
}
