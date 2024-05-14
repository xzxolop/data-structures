#include "hash-table.h"
	
size_t foo(int x) {
	return x * 2;
}



int main() {
	HashTable<int, std::string, stdHash> ht;
	/*ht.insert(std::pair<int, std::string>(1, "d"));
	ht.insert(std::pair<int, std::string>(2, "d"));
	ht.insert(std::pair<int, std::string>(3, "d"));
	ht.insert(std::pair<int, std::string>(4, "d"));
	ht.insert(std::pair<int, std::string>(5, "d"));
	ht.insert(std::pair<int, std::string>(6, "d"));
	ht.insert(std::pair<int, std::string>(7, "d"));*/

	ht.insert(1, "ban");
	ht.insert(2, "egor");
	ht.insert(360, "niger");
	ht.print();
	std::cout << ht.operator[](2);

	return 0;
}