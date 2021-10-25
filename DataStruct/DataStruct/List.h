#pragma once
#include "ListNode.h"

template<class T>
class List {
private:
	int _size;	//��ģ
	Posi(T) header; Posi(T) trailer;	//ͷ,β�ڱ�
protected:
	void init();
	void copyNodes(Posi(T) p, int n);
public:
	List() { init(); }
	List(List<T> const& L);
	List(List<T> const& L, int n);
	List(Posi(T) p, int n);

	~List();		//��������

	Posi(T) insert(T const& e, Posi(T) p);	//��e����p��ǰ��
	Posi(T) insert(Posi(T) p, T const& e);	//��e����p�ĺ��
	Posi(T) insert(T const& e);				//��e��Ϊĩ�ڵ����
	Posi(T) insertAsLast(T const& e);		//��e��Ϊĩ�ڵ����

	T remove(Posi(T) p);		//ɾ��һ���ڵ�
	int clear();			//ɾ�����нڵ�
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
void List<T>::copyNodes(Posi(T) p, int n) {
	init();
	while (n--) {
		insert(p->data);
		p = p->succ;
	}
}

template<class T>
List<T>::List(List<T> const& L) {
	copyNodes(L.header->succ, _size);
}

template<class T>
List<T>::List(List<T> const& L, int n) {
	copyNodes(L.header->succ, n);
}

template<class T>
List<T>::List(Posi(T) p, int n) {
	copyNodes(p, n);
}

template<class T>
List<T>::~List() {
	clear();
	delete header;
	delete trailer;
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
	return insertAsLast(e);
}

template<class T>
Posi(T) List<T>::insertAsLast(T const& e) {
	return insert(e, trailer);
}

template<class T>
T List<T>::remove(Posi(T) p) {
	T e = p->data;
	p->succ->pred = p->pred;
	p->pred->succ = p->succ;
	_size--;
	delete p;
	return e;
}

template<class T>
int List<T>::clear() {
	int oldSize = _size;
	while (_size > 0) remove(header->succ);
	return oldSize;
}