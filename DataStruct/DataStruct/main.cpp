#include "Vector.h"
#include <iostream>

void mout(int e) {
	
	std::cout << e-- << std::endl;
}

int main() {
	Vector<int> v1;
	v1.insert(11);
	v1.insert(10);
	v1.insert(9);
	v1.insert(4);
	v1.insert(3);
	v1.insert(2);
	v1.insert(1);
	v1.bubbleSort();
	//int p = v1.fibSearch(7);
	//std::cout << p << std::endl;
//	v1.bubbleSort(0, 3);
	v1.unsort();
	v1.traverse(mout);

	return	0;
}