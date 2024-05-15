#include "hash-table.h"
#include <unordered_map>

int main() {
	HashTable<int, std::string, stdHash> ht;
	ht.insert(std::pair<int, std::string>(1, "d1"));
	ht.insert(std::pair<int, std::string>(2, "d2"));
	ht.insert(std::pair<int, std::string>(3, "d3"));
	ht.insert(std::pair<int, std::string>(4, "d4"));
	ht.insert(std::pair<int, std::string>(5, "d5"));
	ht.insert(std::pair<int, std::string>(6, "d6"));
	ht.insert(std::pair<int, std::string>(7, "d7"));

	ht.insert(1, "ban");
	ht.insert(2, "egor");
	ht.insert(360, "niger");
	ht.print();

	std::cout << ht.operator[](2) << std::endl;

	std::unordered_map<int, std::string> htstd;

	return 0;
}