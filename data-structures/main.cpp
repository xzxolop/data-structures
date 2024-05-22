#include <unordered_map>
#include <ctime>

#include "hash-table.h"

int main() {
	std::srand(std::time(0));

	HashTable<int, std::string, stdHash> ht1;
	HashTable<int, std::string, myHash> ht2;
	HashTable<int, std::string, alikHash> ht3;


	int a = 2000;
	while (a) {
		ht1.insert(std::rand()%10, "a");
		ht2.insert(std::rand() % 10, "b");
		ht3.insert(std::rand() % 10, "c");
		a--;
	}
	ht1.hash_print();
	ht2.hash_print();
	ht3.hash_print();
	std::cout << std::endl;


	return 0;
}