#pragma once

#include <algorithm>
#include <iostream>

class Elem {
private:
	int data;
	static size_t assings, compares;
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

	bool operator<(const Elem& other) const {
		++compares;
		return data < other.data;
	}
	bool operator>(const Elem& other) const {
		++compares;
		return data > other.data;
	}

	static void reset() {
		assings = 0;
		compares = 0;
	}

	static void print() {
		std::cout << "assings: " << assings << " " << "compares: " << compares << std::endl;
	}

	friend std::ostream& operator<<(std::ostream& out, const Elem& item) {
		return out << item.data;
	}
};

size_t Elem::assings = 0;
size_t Elem::compares = 0;