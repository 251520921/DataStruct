#pragma once
#include "ListNode.h"

template<class T>
class List {
private:
	int _size;	//��ģ
	Posi(T) header; Posi(T) trailer;	//ͷ,β�ڱ�
protected:
	void init();
public:
	List() { init(); }

	Posi(T) insert(T const& e, Posi(T) p);	//��e����p��ǰ��
	Posi(T) insert(Posi(T) p, T const& e);	//��e����p�ĺ��
	Posi(T) insert(T const& e);				//��e�������һ��Ԫ��
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