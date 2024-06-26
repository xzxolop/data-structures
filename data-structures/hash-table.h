﻿#pragma once
#include <string>
#include <array>
#include <vector>
#include <list>
#include <iostream>

template<typename Key>
size_t stdHash(Key key) {
	auto bytes = &reinterpret_cast<const unsigned char&>(key);
	size_t hash = 0;
	for (int i = 0; i < sizeof(key); i++) {
		hash ^= static_cast<size_t>(bytes[i]);
		hash *= i + 1;
		//std::hash<std::string>()
	}

	return hash;
}

template<typename Key>
size_t myHash(Key key) {
	auto bytes = &reinterpret_cast<const unsigned char&>(key);
	size_t hash = 0;
	for (int i = 0; i < sizeof(key); i++) {
		hash ^= static_cast<size_t>(bytes[i]);
	}
	return hash;
}

template<typename Key>
size_t alikHash(Key key) {
	auto bytes = &reinterpret_cast<const unsigned char&>(key);
	size_t hash = 0;
	for (int i = 0; i < sizeof(key); i++) {
		hash = (hash << 5) + static_cast<size_t>(bytes[i]);
	}

	return hash;
}


// Analog of unordered_multimap
template<typename Key, typename Value, size_t(*Hash)(Key)>
class HashTable {
public:
	using value_type = std::pair<const Key, Value>;
	using reference = value_type&;
	using pointer = value_type*;
	using mylist = std::list<value_type>;
	using Fun = size_t(*)(Key);

	HashTable() : _size(0), buckets(std::vector<mylist>(7)) {}; // использовать список инициализации, для большей эффективности

	void insert(const Key k, const Value& v) { // почему value не следует делать const?
		insert(k, std::move(Value(v)));
	}

	void insert(const Key k, Value&& v) {
		if (buckets.size() * _resizer < _size) {
			_resize();
		}
		else {
			size_t ind = get_index(k);
			if (buckets[ind].size()) {
				colison_count++;
			}
			buckets[ind].push_back(value_type(k, v));
			_size++;
		}
	}

	void insert(const value_type& pair) {
		insert(std::move(value_type(pair)));
	}

	void insert(value_type&& pair) {
		if (buckets.size() * _resizer < _size) {
			_resize();
		}
		else {
			size_t ind = get_index(pair.first);
			if (buckets[ind].size()) {
				colison_count++;
			}
			buckets[ind].push_back(pair);
			_size++;
		}
	}

	void remove(Key key) {
		size_t ind = get_index(key);
		mylist* l = &buckets[ind];

		for (auto it = l->begin(); it != l->end(); ) {
			if (it->first == key) {
				it = l->erase(it);
			}
			else {
				it++; // если убрать else будет ошибка?
			}
		}
	}

	void remove_first(Key key) {
		size_t ind = get_index(key);
		mylist* l = &buckets[ind];

		for (auto it = l->begin(); it != l->end(); ) {
			if (it->first == key) {
				it = l->erase(it);
				return;
			}
			else {
				it++;
			}
		}
	}

	void remove_last(Key key) {
		size_t ind = get_index(key);
		mylist* l = &buckets[ind];

		for (auto it = l->end(); it != l->begin(); ) {
			--it;
			if (it->first == key) {
				it = l->erase(it);
				return;
			}
			else {
				--it;
			}
		}
	}

	void remove(Key key, size_t position) {
		size_t ind = get_index(key);
		mylist* l = &buckets[ind];

		for (auto it = l->end(); it != l->begin(); position >= 0) {
			if (it->first == key) {
				position--;
				if (position == 0) {
					it = l->erase(it);
					l = nullptr;
					return;
				}
			}
			else {
				--it;
			}
		}
		l = nullptr;
	}

	auto find(const Key& key) const { // ключ передавать по ссылке или значению?
		size_t ind = get_index(key);

		if (buckets[ind].begin()) {
			return buckets.begin();
		}
		return nullptr;
	}

	bool find(const Key& key, const Value& value) { // нужен ли move
		size_t ind = get_index(key);
		mylist* l = &(buckets[ind]);

		for (auto it = l->begin(); it != l->end(); ) {
			if (it->second == value) {
				l = nullptr;
				return true;
			}
			it++;
		}
		l = nullptr;
		return false;
	}

	Fun hash_function() const {
		return Hash;
	}

	void print() const {
		for (size_t i = 0; i < buckets.size(); i++) {
			if (buckets[i].size() > 0) {
				std::cout << i << ": ";
				for (auto x : buckets[i]) {
					std::cout << x.second << ' ';
				}
				std::cout << std::endl;
			}
		}
	}

	void hash_print() const {
		for (size_t i = 0; i < buckets.size(); i++) {
			if (buckets[i].size() > 0) {
				std::cout << i << ": " << Hash((buckets[i].begin())->first) << ": ";
				for (auto x : buckets[i]) {
					std::cout << x.second << ' ';
				}
				std::cout << std::endl;
			}
		}
	}

	Value& operator[](Key key) {
		size_t ind = get_index(key);
		
		for (auto& x : buckets[ind]) { // auto с ссылкой? без ссылки не работает.
			if (x.first == key) {
				return x.second;
			}
			else {
				throw 0;
			}
		}
	}

	size_t avarage_colision() const {
		size_t fill_buckets = 0 ;
		for (auto x : buckets) {
			if (x.size() > 0) {
				fill_buckets++;
			}
		}
		return colison_count/fill_buckets;
	}

private:
	int _size = 0;
	size_t colison_count = 0;
	std::vector<mylist> buckets; // стоит ли использовать это как указатель на вектор? как на счёт конструктора копии?
	int _resizer = 7;

	int get_index(Key key) const {
		return Hash(key) % buckets.size();
	}

	std::vector<int> sizes{5, 11, 23, 47, 97, 193, 389, 769, 1543, 3072, 3079, 12289, 24593,
		49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843,
		50331653, 100663319, 201326611, 402653189, 805306457, 1610612736, 2147483629};

	void _resize() {
		int new_size = buckets.size();
		for (int i = 1; i < sizes.size(); i++ ) {
			if (new_size < sizes[i]) {
				new_size = sizes[i];
				buckets.resize(new_size);
				return;
			}
		}
	}
};


