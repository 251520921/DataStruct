#include "Vector.h"
#include <iostream>

void mout(int e) {
	
	std::cout << e-- << std::endl;
}

int main() {
	Vector<int> v1;
	v1.insert(10);
	v1.insert(9);
	v1.insert(8);
	v1.mergeSort();
//	v1.bubbleSort(0, 3);
	v1.traverse(mout);

	return	0;
}