#include "hash-table.h"
#include <unordered_map>

int main() {
	HashTable<int, std::string, stdHash> ht;
	ht.insert(1, "ban");
	ht.insert(2, "egor");
	ht.insert(360, "niger");
	ht.insert(360, "ni34ger");
	ht.print();

	//std::cout << ht.operator[](2) << std::endl;
	auto p = ht.operator[](360);
	std::cout << *p;

	std::unordered_map<int, std::string> htstd;

	return 0;
}