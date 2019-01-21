#ifndef _BIN_NODE_H_
#define _BIN_NODE_H_

#define BinNodePosi(T) BinNode<T> *
#define stature(p) ((p) ? (p)->height : -1)		//返回节点高度，空树为-1
typedef enum{
	RB_RED,
	RB_BLACK
}RBColor;

template <typename T>
struct BinNode
{
	T data;
	BinNodePosi(T) parent;
	BinNodePosi(T) lChild;
	BinNodePosi(T) rChild;
	int height;
	int npl;	//Null path length	左式堆
	RBColor color;
	
	BinNode() 
		: parent(NULL), LChild(NULL), rChild(NULL), height(0), npl(1), color(RB_RED)
	{

	}
	BinNde(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc, 
			int h = 0, int l = 1, RBColor c = RB_RED)
		:data(e), parent(p), lChild(lc), rChild(rc), height(h), npl(l), color(c)
	{

	}

	int size();
	BinNodePosi(T) insertAsLC(T const &e);
	BinNodePosi(T) insertAsRC(T const &e);
	BinNodePosi(T) succ();

	template <typename VST> void travLevel(VST&);
	template <typename VST> void travPre(VST&);
	template <typename VST> void travIn(VST&);
	template <typename VST> void travPost(VST&);

	bool operator<(BinNode const &bn)
	{
		return data < bn.data;
	}

	bool operator==(BinNode const &bn)
	{
		return data == bn.data;
	}
};

#endif	//binNode.h
