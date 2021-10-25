#pragma once
#include "ListNode.h"

template<class T>
class List {
private:
	int _size;	//规模
	Posi(T) header; Posi(T) trailer;	//头,尾哨兵
protected:
	void init();
public:
	List() { init(); }

	Posi(T) insert(T const& e, Posi(T) p);	//将e插入p的前驱
	Posi(T) insert(Posi(T) p, T const& e);	//将e插入p的后继
	Posi(T) insert(T const& e);				//将e插入最后一个元素
};

template<class T>
void List<T>::init() {
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer;	header->pred = nullptr;
	trailer->pred = header;	trailer->succ = nullptr;

	_size = 0;
}

template<class T>
Posi(T) List<T>::insert(T const& e, Posi(T) p) {
	_size++;
	return p->insertAsPred(e);
}

template<class T>
Posi(T) List<T>::insert(Posi(T) p, T const& e) {
	_size++;
	return p->insertAsSucc(e);
}

template<class T>
Posi(T) List<T>::insert(T const& e) {
	return insert(e, trailer);
}