#include "hash-table.h"
	
size_t foo(int x) {
	return x * 2;
}



int main() {
	HashTable<int, std::string, myHash> ht;
	ht.insert(std::pair<int, std::string>(1, "d"));
	ht.insert(std::pair<int, std::string>(2, "d"));
	ht.insert(std::pair<int, std::string>(3, "d"));
	ht.insert(std::pair<int, std::string>(4, "d"));
	ht.insert(std::pair<int, std::string>(5, "d"));
	ht.insert(std::pair<int, std::string>(6, "d"));
	ht.insert(std::pair<int, std::string>(7, "d"));


	//auto h_func = ht.hash_function();

	//std::vector<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9};
	//std::cout << myHash(a) << std::endl;


	return 0;
}