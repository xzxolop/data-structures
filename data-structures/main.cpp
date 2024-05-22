#include "hash-table.h"
#include <unordered_map>
#include <list>

int main() {
	HashTable<int, std::string, stdHash> ht;
	ht.insert(1, "ban");
	ht.insert(2, "egor");
	ht.insert(360, "niger");
	ht.insert(360, "ni34ger");
	ht.insert(360, "ni34ger");
	ht.print();

	std::cout << ht.operator[](2) << std::endl;
	
	ht[1] = "22";
	ht.remove_last(360);

	ht.hash_print();


	std::unordered_map<int, std::string> htstd;


	return 0;
}