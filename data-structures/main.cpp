#include <unordered_map>
#include <ctime>
#include <chrono>

#include "hash-table.h"
#include "binary-tree.h"
#include "sort.h"

void binary_tree();
void hash_table();
void bubble_sort_test();

int main() {
	//binary_tree();

	bubble_sort_test();

	return 0;
}

void bubble_sort_test() {

	std::vector<int> v{9, 8, 7, 6, 5, 4, 3, 2, 1, 6, 6};
	for (auto x : v) {
		std::cout << x << ' ';
	}
	std::cout << std::endl;

	bubble_sort1(v);
	for (auto x : v) {
		std::cout << x << ' ';
	}
	std::cout << std::endl;

	v = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 6, 6 };
	bubble_sort2(v.begin(), v.end());
	for (auto x : v) {
		std::cout << x << ' ';
	}
	std::cout << std::endl;

}

void binary_tree() {
	BinaryTree<int> btr;
	btr.insert(10);
	btr.insert(20);
	btr.insert(6);
	btr.insert(1);
	btr.print();

	std::cout << "left: " << btr.left() << " right: " << btr.right() << std::endl;
	std::cout << "size: " << btr.size() << std::endl;
}

void hash_table() {
	std::srand(std::time(0));

	HashTable<int, std::string, stdHash> ht1;
	HashTable<int, std::string, myHash> ht2;
	HashTable<int, std::string, alikHash> ht3;

	int keySize = 1000;
	int a = 2000;
	while (a) {
		ht1.insert(std::rand() % keySize, "a");
		ht2.insert(std::rand() % keySize, "b");
		ht3.insert(std::rand() % keySize, "c");
		a--;
	}
	ht1.hash_print();
	ht2.hash_print();
	ht3.hash_print();
	std::cout << std::endl;

	std::cout << "average collision with stdHash " << ht1.avarage_colision() << std::endl;
	std::cout << "average collision with myHash " << ht2.avarage_colision() << std::endl;
	std::cout << "average collision with alikHash " << ht3.avarage_colision() << std::endl;


	std::cout << std::endl;
	std::cout << "Battle with std" << std::endl;
	std::unordered_multimap<int, std::string> htstd;

	int contSize = 5000000;

	using namespace std::chrono;
	std::cout << "Insertion" << std::endl;
	{
		std::unordered_multimap<int, std::string> htstd2;
		auto start = high_resolution_clock::now();
		a = contSize;
		while (a) {
			htstd2.insert(std::pair<int, std::string>(std::rand() % keySize, "a"));
			a--;
		}

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(end - start);

		std::cout << "std unordered_multimap millisec: " << duration.count() << std::endl;
	}



	HashTable<int, std::string, stdHash> myht;
	{
		auto start = high_resolution_clock::now();

		a = contSize;
		while (a) {
			myht.insert(std::pair<int, std::string>(std::rand() % keySize, "a"));
			a--;
		}

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(end - start);

		std::cout << "my-table stdhash millisec: " << duration.count() << std::endl;
	}

	HashTable<int, std::string, alikHash> myht2;
	{
		auto start = high_resolution_clock::now();

		a = contSize;
		while (a) {
			myht2.insert(std::pair<int, std::string>(std::rand() % keySize, "a"));
			a--;
		}

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(end - start);

		std::cout << "my-table alikhash millisec: " << duration.count() << std::endl;
	}

	HashTable<int, std::string, myHash> myht3;
	{
		auto start = high_resolution_clock::now();

		a = contSize;
		while (a) {
			myht3.insert(std::pair<int, std::string>(std::rand() % keySize, "a"));
			a--;
		}

		auto end = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(end - start);

		std::cout << "my-table myhash millisec: " << duration.count() << std::endl;
	}
}