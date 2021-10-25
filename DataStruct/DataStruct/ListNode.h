#pragma once
//位置
#define Posi(T) ListNode<T>*

template<class T>
class ListNode {
protected:
	
public:
	T data;
	Posi(T) pred;
	Posi(T)	succ;

	ListNode() {}	//针对header和trailer的构造
	ListNode(T const& e, Posi(T) p = NULL, Posi(T) s = NULL)
		:data(e), pred(p), succ(s) {};	//默认构造器

	Posi(T) insertAsPred(T const& e);	//前插入
	Posi(T) insertAsSucc(T const& e);	//后插入
};

/// <summary>
/// 前插入
/// </summary>
/// <param name="e">待插入的值</param>
/// <returns>返回插入的位置</returns>
template<class T>
Posi(T) ListNode<T>::insertAsPred(T const& e) {
	Posi(T) p = new ListNode<T>(e, this->pred, this);
	this->pred->succ = p;
	this->pred = p;
	return p;
}

template<class T>
Posi(T) ListNode<T>::insertAsSucc(T const& e) {
	Posi(T) p = new ListNode<T>(e, this, this->succ);
	this->succ->pred = p;
	this->succ = p;
	return p;
}