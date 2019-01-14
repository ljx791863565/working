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
