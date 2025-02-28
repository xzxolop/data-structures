#pragma once
#include <iostream>
#include <chrono>
#include "stringelem.h"
#include "elem.h"

template<typename cont>
inline void print(const cont& c) {
	for (auto x : c) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
}

template<typename cont>
inline cont& create_cont(cont& c, size_t size) {
	c.clear();
	while (size > 0) {
		c.push_back(static_cast<cont::value_type>(size));
		size--;
	}
	return c;
}

template<typename f, typename... arg>
inline void time_test(f&& fun, arg&&... args) {
	auto start = std::chrono::high_resolution_clock::now();
	std::forward<f>(fun)(std::forward<arg>(args)...);
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << (std::chrono::duration_cast<std::chrono::milliseconds>(end - start)).count() << " milisec" << std::endl;
}

template<typename f, typename... arg>
inline void time_test_nanosec(f&& fun, arg&&... args) {
	auto start = std::chrono::high_resolution_clock::now();
	std::forward<f>(fun)(std::forward<arg>(args)...);
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)).count() << " nanosec" << std::endl;
}


inline std::string revertNumberByString(Elem n) {

	StringElem res;
	Elem is_negative(1);
	if (n < 0) {
		res = res + "-";
		n = n * -1;
	}

	while (n > 0) {
		res = res + std::to_string(n % 10);
		n = n / 10;
	}

	return res;
}

template<typename T>
inline T revertNumberByDivide(T n) {

	T result(0);
	T isNegative(1);
	if (n < 0) {
		isNegative = isNegative * -1;
		n = n * -1;
	} 

	while (n > 0) {
		result = result * 10;
		result = result + (n % 10);
		n = n / 10;
	}

	result = result * isNegative;

	return result;
}


