#pragma once
#include <stdlib.h>
#include <time.h>

#define DEFAULT_CAPACITY 16
using Rank = int;

template<class T>
class Vector {
private:
	T* _elem; int _size; int _capacity;		//数据区,当前容量,最大容量
	void copyFrom(T const* A, Rank lo, Rank hi);	//复制构造
protected:
	//可写
	void expand();		//扩容
	void shrink();		//缩容
	void swap(T& l, T& r);	//交换元素

	Rank bubble(Rank lo, Rank hi);
	Rank maxItem(Rank lo, Rank hi);
	void merge(Rank lo, Rank mi, Rank hi);
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
	Rank find(T const& e, Rank lo, Rank hi) const;//查找
	Rank find(T const& e) const;		//查找
	

	//可写接口
	Rank insert(Rank r, T const& e);		//插入
	Rank insert(T const& e);		//插入
	Rank remove(Rank lo, Rank hi);	//区域删除
	T remove(Rank n);		//删除
	Rank clear();		//清空
	int deduplicate();	//去除重复元素

	void bubbleSort(Rank lo, Rank hi);	//冒泡排序
	void bubbleSort();
	void selectSort(Rank lo, Rank hi);	//选择排序
	void selectSort();
	void mergeSort(Rank lo, Rank hi);	//归并排序
	void mergeSort();
	

	//遍历
	void traverse(void (*visit)(T&));	//函数指针
	template<class VST>void traverse(VST& visit);		//函数对象
	void retraverse(void (*visit)(T&));	//逆序遍历
	template<class VST> void retraverse(VST& visit);	//逆序遍历

	//静态接口
	static int dice(int lo, int hi);	//取[lo,hi)的随机数
	static int dice(int range);			//取[0,range)的随机数
	static float dice(float range);
	static double dice(double range);
	static char dice();	//随机生成一个字符
	
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
/// 交换元素
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="l">待交换元素</param>
/// <param name="r">待交换元素</param>
template<class T>
void Vector<T>::swap(T& l, T& r) {
	T temp = l;
	l = r;
	r = temp;
}

template<class T>
Rank Vector<T>::bubble(Rank lo, Rank hi)
{
	Rank last = lo;
	while (++lo < hi) {
		if (_elem[lo - 1] > _elem[lo]) {
			swap(_elem[lo - 1], _elem[lo]);
			last = lo;
		}
	}
	return last;
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

/// <summary>
/// 查找e在[lo,hi)中的秩
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="e">待查找的值</param>
/// <param name="lo">低区间</param>
/// <param name="hi">高区间</param>
/// <returns>成功返回值在向量中的秩,失败返回小于待查找值的最大秩</returns>
template<class T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const {
	while ((lo < hi--) && (e != _elem[hi]));
	return hi;
}
/// <summary>
/// 查找e在向量中的秩
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="e">要查找的值</param>
/// <returns>成功返回值在向量中的秩,失败返回小于待查找值的最大秩</returns>
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
/// 去除重复元素
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns>返回删除的元素数</returns>
template<class T>
int Vector<T>::deduplicate() {
	int oldSize = _size;
	int i = 1;
	while (i < _size)
		(find(_elem[i], 0, i) < 0) ? i++ : remove(i);
	shrink();
	return oldSize - _size;
}

/// <summary>
/// 冒泡排序法,[lo,hi)
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="lo"></param>
/// <param name="lo">低区间</param>
/// <param name="hi">高区间</param>
template<class T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
	while (lo < (hi = bubble(lo, hi)));
}

template<class T>
void Vector<T>::bubbleSort() {
	bubbleSort(0, _size);
}

/// <summary>
/// 选择排序
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="lo"></param>
/// <param name="hi"></param>
template<class T>
void Vector<T>::selectSort(Rank lo, Rank hi) {
	while (lo < --hi)
		swap(_elem[maxItem(lo, hi)], _elem[hi]); //将[lo,hi]中的最大者与hi交换
}

template<class T>
void Vector<T>::selectSort() {
	selectSort(0, _elem);
}

/// <summary>
/// 归并排序
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="lo">低区间</param>
/// <param name="hi">高区间</param>
template<class T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if ((hi - lo) < 2) return;
	Rank mi = (lo + hi) >> 1;
	mergeSort(lo, mi);
	mergeSort(mi, hi);
	merge(lo, mi, hi);
}

template<class T>
void Vector<T>::mergeSort() {
	mergeSort(0, _size);
}

template<class T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
	Rank i = 0; T* A = _elem + lo;
	Rank j = 0; int lb = mi - lo; T* B = new T[lb];
	for (int i = 0; i < lb; i++) B[i] = A[i];
	Rank k = 0; int lc = hi - mi; T* C = _elem + mi;
	while (j < lb && k < lc) A[i++] = (B[j] <= C[k]) ? B[j++] : C[k++];
	while (j < lb) A[i++] = B[j++];
	delete[] B;
}

/// <summary>
/// 在[lo,hi]中找出最大者
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="lo">低区间</param>
/// <param name="hi">高区间</param>
/// <returns>返回最大者的秩</returns>
template<class T>
Rank Vector<T>::maxItem(Rank lo, Rank hi) {
	Rank mx = hi;
	while (lo < hi--)	//逆序扫描
		if (_elem[hi] > _elem[mx])	//严格比较找出最大者
			mx = hi;	//故能在max有多个时保证后者优先，进而保证selectionSort稳定
	return mx;
}
/// <summary>
/// 遍历向量
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="visit">函数指针</param>
template<class T>
void Vector<T>::traverse(void (*visit)(T&)) {
	for (int i = 0; i < _size; i++)
		visit(_elem[i]);
}

/// <summary>
/// 遍历向量
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="visit">函数对象</param>
template<class T> template<class VST>
void Vector<T>::traverse(VST& visit) {
	for (int i = 0; i < _size; i++)
		visit(_elem[i]);
}

template<class T>
void Vector<T>::retraverse(void (*visit)(T&)) {
	for (int i = _size - 1; i >= 0; i--)
		visit(_elem[i]);
}

template<class T> template<class VST>
void Vector<T>::retraverse(VST& visit) {
	for (int i = _size - 1; i >= 0; i--)
		visit(_elem[i]);
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
	return rand() % (1000 * (int)range) / (float)1000.; //取三位小数
}

template<class T>
double Vector<T>::dice(double range) {
	srand((unsigned)time(NULL));
	return rand() % (100 * (int)range) / (float)100.;	//取两位小数
}

template<class T>
char Vector<T>::dice() {
	srand((unsigned)time(NULL));
	return (char)(32 + rand() % 96);
}