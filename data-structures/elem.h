#pragma once

#include <algorithm>
#include <iostream>

class Elem {
private:
	int data;
	static size_t assings;
	static size_t compares;
	static size_t mult;
	static size_t div;
	static size_t mod;
	static size_t add;
public:
	

	Elem() : data(rand()) {};
	explicit Elem(int a) : data(a) {};
	Elem(const Elem& other) : data(other.data) {
		++assings;
	}
	
	const Elem& operator=(const Elem& other) {
		++assings;
		data = other.data;
		return *this;
	}
	const Elem& operator=(const int& other) {
		++assings;
		data = other;
		return *this;
	}

	bool operator<(const Elem& other) const {
		++compares;
		return data < other.data;
	}
	bool operator>(const Elem& other) const {
		++compares;
		return data > other.data;
	}

	bool operator<(const int& other) const {
		++compares;
		return data < other;
	}
	bool operator>(const int& other) const {
		++compares;
		return data > other;
	}

	Elem operator*(const Elem& other) const {
		++mult;
		return Elem(data * other.data);
	}

	Elem operator/(const Elem& other) const {
		if (other.data == 0) {
			throw std::invalid_argument("Division by zero");
		}
		++div;
		return Elem(data / other.data);
	}

	Elem operator%(const Elem& other) const {
		if (other.data == 0) {
			throw std::invalid_argument("Modulo by zero");
		}
		++mod;
		return Elem(data % other.data);
	}

	Elem operator*(const int& other) const {
		++mult;
		return Elem(data * other);
	}

	Elem operator/(const int& other) const {
		if (other == 0) {
			throw std::invalid_argument("Division by zero");
		}
		++div;
		return Elem(data / other);
	}

	Elem operator%(const int& other) const {
		if (other == 0) {
			throw std::invalid_argument("Modulo by zero");
		}
		++mod;
		return Elem(data % other);
	}

	Elem operator+(const Elem& other) const {
		++add;
		return Elem(data + other.data);
	}
	Elem operator+(const int& other) const {
		++add;
		return Elem(data + other);
	}

	operator int() const {
		return data;
	}

	static void reset() {
		assings = 0;
		compares = 0;
		mult = 0;
		div = 0;
		mod = 0;
		add = 0;
	}

	static void print() {
		size_t total = 0;

		total = assings + compares + mult + div + mod + add;

		std::cout << " total int operations: " << total << " assings: " << assings << " compares: " << compares 
			<< " mult: " << mult << " div: " << div << " mod: " << mod << " add: " << add
			 << std::endl;
	}

	friend std::ostream& operator<<(std::ostream& out, const Elem& item) {
		return out << item.data;
	}
};

size_t Elem::assings = 0;
size_t Elem::compares = 0;
size_t Elem::mult = 0;
size_t Elem::div = 0;
size_t Elem::mod = 0;
size_t Elem::add = 0;