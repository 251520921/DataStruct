#include <iostream>
#include "List.h"


int main() {
	List<int> list;
	
	list.insertAsLast(1);
	list.insertAsLast(2);
	list.insertAsLast(3);
	list.insertAsLast(4);
	list.insertAsLast(5);
	list.insertAsLast(6);
	list.insertAsLast(7);

	list.clear();

	return	0;
}