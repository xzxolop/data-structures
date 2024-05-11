#pragma once
#include <string>
#include <vector>
#include <iostream>

template<typename Key>
size_t myHash(Key key) {
	auto ban = &reinterpret_cast<const unsigned char&>(key);
	size_t hash = 0;
	for (int i = 0; i < sizeof(key); i++) {
		hash ^= static_cast<size_t>(ban[i]);
		hash *= i + 1;
	}

	return hash;
}

template<typename Key>
size_t myHash2(Key key) {
	auto ban = &reinterpret_cast<const unsigned char&>(key);
	size_t hash = 0;
	for (int i = 0; i < sizeof(key); i++) {
		hash = (hash << 8) + static_cast<size_t>(ban[i]);
	}

	return hash;
}


// Analog of unordered_map
template<typename Key, typename Value, size_t (*Hash)(Key)>
class HashTable {
public:
	using value_type = std::pair<Key, Value>;
	using reference = value_type&;
	using pointer = value_type*;

	//typedef size_t (*Fun)(Key);
	using Fun = size_t(*)(Key);

	HashTable() {
		_size = 7;
	}

	Fun hash_function() const {
		return Hash;
	}

	void insert(const value_type& v) {
		std::cout << get_index(v.first) << std::endl;
	}

private:
	int _size = 0;
	std::vector<value_type> buckets;
	int get_index(Key key) const {
		return Hash(key) % _size;
	}
};


