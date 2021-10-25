#pragma once
//λ��
#define Posi(T) ListNode<T>*

template<class T>
class ListNode {
protected:
	
public:
	T data;
	Posi(T) pred;
	Posi(T)	succ;

	ListNode() {}	//���header��trailer�Ĺ���
	ListNode(T const& e, Posi(T) p = NULL, Posi(T) s = NULL)
		:data(e), pred(p), succ(s) {};	//Ĭ�Ϲ�����

	Posi(T) insertAsPred(T const& e);	//ǰ����
	Posi(T) insertAsSucc(T const& e);	//�����
};

/// <summary>
/// ǰ����
/// </summary>
/// <param name="e">�������ֵ</param>
/// <returns>���ز����λ��</returns>
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