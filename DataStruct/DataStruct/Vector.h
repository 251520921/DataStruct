#pragma once
#include <stdlib.h>
#include <time.h>

#define DEFAULT_CAPACITY 16
using Rank = int;

template<class T>
class Vector {
private:
	T* _elem; int _size; int _capacity;		//������,��ǰ����,�������
	void expand();		//����
	void shrink();		//����
	void copyFrom(T const* A, Rank lo, Rank hi);	//���ƹ���
protected:
		
public:
	//���캯��
	Vector(int s = 0, T const& e = 0, int c = DEFAULT_CAPACITY);
	Vector(Vector<T> const& V, Rank lo, Rank hi);
	Vector(Vector<T> const& V);
	Vector(T const* A, Rank lo, Rank hi);
	Vector(T const* A, Rank n);
	
	//��������
	~Vector();
	
	//���غ���
	Vector<T>& operator=(Vector<T> const& rhs);
	T& operator[](Rank r) const;	//����[]
	operator T* () const;			//����ǿ������ת��
	
	//ֻ���ӿ�
	Rank size() const;		//��ȡ��ǰ����
	bool empty() const;		//�Ƿ������
	Rank find(T const& e, Rank lo, Rank hi) const;//����
	Rank find(T const& e) const;		//����
	
	//��д�ӿ�
	Rank insert(Rank r, T const& e);		//����
	Rank insert(T const& e);		//����
	Rank remove(Rank lo, Rank hi);	//����ɾ��
	T remove(Rank n);		//ɾ��
	Rank clear();		//���
	int deduplicate();	//ȥ���ظ�Ԫ��

	//��̬�ӿ�
	static int dice(int lo, int hi);	//ȡ[lo,hi)�������
	static int dice(int range);		//ȡ[0,range)�������
	static float dice(float range);
	static double dice(double range);
	static char dice();	//�������һ���ַ�
	
};

template<class T>
void Vector<T>::expand() {
	if (_size < _capacity) return;
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

template<class T>
void Vector<T>::shrink() {
	if (_size > _capacity >> 2) return;
	if (_capacity >> 1 < DEFAULT_CAPACITY) return;
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

/// <summary>
/// ���ƹ��캯������
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="A">Ҫ���Ƶ������׵�ַ</param>
/// <param name="lo">�͵�ַ</param>
/// <param name="hi">�ߵ�ַ</param>
template<class T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
	_elem = new T[_capacity = (hi - lo) << 1];
	for (_size = 0; lo < hi; _size++, lo++)
		_elem[_size] = A[lo];
}

/// <summary>
/// ���캯��
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="s">��ǰ����</param>
/// <param name="e">Ҫ��ʼ��������</param>
/// <param name="c">�������</param>
template<class T>
Vector<T>::Vector(int s, T const& e, int c) {
	if (s > c) c = s << 1;
	_elem = new T[_capacity = c];
	for (int i = 0; i < s; i++)
		_elem[i] = e;
	_size = s;
}

template<class T>
Vector<T>::Vector(Vector<T> const& V, Rank lo, Rank hi) {
	copyFrom(V._elem, lo, hi);
}

template<class T>
Vector<T>::Vector(Vector<T> const& V) {
	copyFrom(V._elem, 0, V._size);
}

template<class T>
Vector<T>::Vector(T const* A, Rank lo, Rank hi) {
	copyFrom(A, lo, hi);
}

template<class T>
Vector<T>::Vector(T const* A, Rank n) {
	copyFrom(A, 0, n);
}

template<class T>
Vector<T>::~Vector() {
	delete[] _elem;
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector<T> const& rhs) {
	copyFrom(rhs._elem, 0, rhs._size);
}

template<class T>
T& Vector<T>::operator[](Rank r) const {
	return _elem[r];
}

template<class T>
Rank Vector<T>::size() const {
	return _size;
}

template<class T>
Vector<T>::operator T* () const {
	return _elem;
}
template<class T>
bool Vector<T>::empty() const {
	return !_size;
}

/// <summary>
/// ����e��[lo,hi)�е���
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="e">�����ҵ�ֵ</param>
/// <param name="lo">������</param>
/// <param name="hi">������</param>
/// <returns>�ɹ�����ֵ�������е���,ʧ�ܷ���С�ڴ�����ֵ�������</returns>
template<class T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const {
	while ((lo < hi--) && (e != _elem[hi]));
	return hi;
}
/// <summary>
/// ����e�������е���
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="e">Ҫ���ҵ�ֵ</param>
/// <returns>�ɹ�����ֵ�������е���,ʧ�ܷ���С�ڴ�����ֵ�������</returns>
template<class T>
Rank Vector<T>::find(T const& e) const {
	return find(e, 0, _size);
}


template<class T>
Rank Vector<T>::insert(Rank r, T const& e) {
	expand();
	for (int i = _size; i > r; i--)
		_elem[i] = _elem[i - 1];
	_size++;
	_elem[r] = e;
	return r;
}

template<class T>
Rank Vector<T>::insert(T const& e) {
	return insert(_size, e);
}

template<class T>
Rank Vector<T>::remove(Rank lo, Rank hi) {
	if (lo == hi) return 0;
	int oldSize = _size;
	while (hi < _size)
		_elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();
	return hi - lo;
}

template<class T>
T Vector<T>::remove(Rank r) {
	T t = _elem[r];
	remove(r, r + 1);
	return t;
}

template<class T>
Rank Vector<T>::clear() {
	Rank oldSize = _size;
	_size = 0;
	delete[] _elem;
	_elem = new T[_capacity = DEFAULT_CAPACITY];
	return oldSize;
}
/// <summary>
/// ȥ���ظ�Ԫ��
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns>����ɾ����Ԫ����</returns>
template<class T>
int Vector<T>::deduplicate() {
	int oldSize = _size;
	int i = 1;
	while (i < _size)
		(find(_elem[i], 0, i) < 0) ? i++ : remove(i);
	shrink();
	return oldSize - _size;
}

template<class T>
int Vector<T>::dice(int lo, int hi) {
	srand((unsigned)time(NULL));
	return lo + rand() + (hi - lo);
}

template<class T>
int Vector<T>::dice(int range){
	dice(0, range);
}

template<class T>
float Vector<T>::dice(float range) {
	srand((unsigned)time(NULL));
	return rand() % (1000 * (int)range) / (float)1000.; //ȡ��λС��
}

template<class T>
double Vector<T>::dice(double range) {
	srand((unsigned)time(NULL));
	return rand() % (100 * (int)range) / (float)100.;	//ȡ��λС��
}

template<class T>
char Vector<T>::dice() {
	srand((unsigned)time(NULL));
	return (char)(32 + rand() % 96);
}