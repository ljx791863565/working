#ifndef __LISTNODE__H__
#define __LISTNODE__H__

#include <iostream>
#include <cstdlib>
#include <cassert>
typedef int Rank;
#define ListNodePosi(T) ListNode<T> *

template <typename T>
struct ListNode
{
	T data;
	ListNodePosi(T) succ;		//后继
	ListNodePosi(T) pred;		//前驱

	ListNode()
	{

	}
	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
		: data(e), succ(s), pred(p)
	{

	}

	ListNodePosi(T) insertAsPred(T const &e);
	ListNodePosi(T) insertAsSucc(T const &e);

};


#endif
