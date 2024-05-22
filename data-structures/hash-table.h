#pragma once
#include <string>
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
template<typename Key, typename Value, size_t(*Hash)(Key)>
class HashTable {
public:
	using value_type = std::pair<Key, Value>;
	using reference = value_type&;
	using pointer = value_type*;
	using list = std::list<value_type>;
	using Fun = size_t(*)(Key);

	HashTable() {
		_size = 7;
		buckets = std::vector<list>(_size);
	}

	void insert(const Key k, const Value& v) { // почему value не следует делать const?
		insert(k, std::move(value(v)));
	}

	void insert(const Key k, Value&& v) {
		size_t ind = get_index(k);
		buckets[ind].push_back(value_type(k,v));
	}

	void insert(const value_type& pair) {
		insert(std::move(value_type(pair)));
	}

	void insert(value_type&& pair) {
		size_t ind = get_index(pair.first);
		buckets[ind].push_back(pair);
	}

	void remove(Key key) {
		size_t ind = get_index(key);
		list* l = &buckets[ind];

		for (auto it = l->begin(); it != l->end(); ) {
			if (it->first == key) {
				it = l->erase(it);
			}
			else {
				it++; // если убрать else будет ошибка?
			}
		}

		/*for (auto it = l->begin(); it != l->end(); ++it ) { 
			if (it->first == key) {
				it = l->erase(it);
			}
		}*/
	}

	void remove_first(Key key) {
		size_t ind = get_index(key);
		list* l = &buckets[ind];

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
		list* l = &buckets[ind];

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
		list* l = &buckets[ind];

		for (auto it = l->end(); it != l->begin(); position >= 0) {
			if (it->first == key) {
				position--;
				if (position == 0) {
					it = l->erase(it);
					return;
				}
			}
			else {
				--it;
			}
		}
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

private:
	int _size = 0;
	std::vector<list> buckets; // стоит ли использовать это как указатель на вектор? как на счёт конструктора копии?

	int get_index(Key key) const {
		return Hash(key) % _size;
	}
};


