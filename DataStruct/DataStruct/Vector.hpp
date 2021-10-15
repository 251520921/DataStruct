#pragma once

#define DEFAULT_CAPACITY 16
using Rank = int;

template<class T>
class Vector {
private:
	T* _elem; int _size; int _capacity;		//数据区,当前容量,最大容量
	void expand();		//扩容
	void shrink();		//缩容
	void copyFrom(T const* A, Rank lo, Rank hi);	//复制构造
protected:
		
public:
	//构造函数
	Vector(int s = 0, T const& e = 0, int c = DEFAULT_CAPACITY);
	Vector(Vector<T> const& V, Rank lo, Rank hi);
	Vector(Vector<T> const& V);
	Vector(T const* A, Rank lo, Rank hi);
	Vector(T const* A, Rank n);
	//析构函数
	~Vector();
	//重载函数
	Vector<T>& operator=(Vector<T> const& rhs);
	T& operator[](Rank r) const;	//重载[]
	operator T* () const;			//重载强制类型转换
	//只读接口
	Rank size() const;		//获取当前容量
	bool empty() const;		//是否空向量
	//可写接口
	Rank insert(Rank r, T const& e);		//插入
	Rank insert(T const& e);		//插入
	Rank remove(Rank lo, Rank hi);	//区域删除
	T remove(Rank n);		//删除
	Rank clear();		//清空
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
/// 复制构造函数调用
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="A">要复制的数据首地址</param>
/// <param name="lo">低地址</param>
/// <param name="hi">高地址</param>
template<class T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
	_elem = new T[_capacity = (hi - lo) << 1];
	for (_size = 0; lo < hi; _size++, lo++)
		_elem[_size] = A[lo];
}

/// <summary>
/// 构造函数
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="s">当前容量</param>
/// <param name="e">要初始化的数据</param>
/// <param name="c">最大容量</param>
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