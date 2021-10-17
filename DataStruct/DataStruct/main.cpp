#include "Vector.h"
#include <iostream>

void mout(int e) {
	
	std::cout << e-- << std::endl;
}

int main() {
	Vector<int> v1(10,8);
	v1.insert(9);
	v1.insert(10);
	v1.insert(0, 1);
	v1.insert(1, 2);
	v1.traverse(mout);
	std::cout << "****************************" << std::endl;
	v1.retraverse(mout);
	return	0;
}