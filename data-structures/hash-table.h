#pragma once
#include <string>
#include <vector>
#include <iostream>

template<typename Key>
size_t stdHash(Key key) {
	auto bytes = &reinterpret_cast<const unsigned char&>(key);
	size_t hash = 0;
	for (int i = 0; i < sizeof(key); i++) {
		hash ^= static_cast<size_t>(bytes[i]);
		hash *= i + 1;
	}

	return hash;
}

template<typename Key>
size_t alikHash(Key key) {
	auto bytes = &reinterpret_cast<const unsigned char&>(key);
	size_t hash = 0;
	for (int i = 0; i < sizeof(key); i++) {
		hash = (hash << 8) + static_cast<size_t>(bytes[i]);
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
		buckets = std::vector<Value>(_size);
	}

	void insert(const Key k, const Value& v) { // почему value не следует делать const?
		insert(std::move(Value(v)));
	}

	void insert(const Key k, Value&& v) {
		size_t ind = get_index(k);
		buckets[ind] = v;
	}

	void insert(const value_type& pair) {
		insert(std::move(value_type(pair)));
	}

	void insert(value_type&& pair) {
		size_t ind = get_index(pair.first);
		buckets[ind] = pair.second;
	}

	Fun hash_function() const {
		return Hash;
	}

	void print() const {
		for (int i = 0; i < buckets.size(); i++) {
			std::cout << i << ": " << buckets[i] << std::endl;
		}
	}

	Value& operator[](Key key) {
		size_t ind = get_index(key);
		return buckets[ind];
	}

private:
	int _size = 0;
	std::vector<Value> buckets;
	int get_index(Key key) const {
		return Hash(key) % _size;
	}
};


