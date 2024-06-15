#pragma once
#include <iostream>
#include <chrono>

template<typename cont>
inline void print(const cont& c) {
	for (auto x : c) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
}

template<typename cont, typename T>
inline cont& create_cont(cont& c, size_t size) {
	c.clear();
	while (size > 0) {
		c.push_back((T)size);
		size--;
	}
	return c;
}

template<typename f, typename... arg>
void time_test(f&& fun, arg&&... args) {
	auto start = std::chrono::high_resolution_clock::now();
	std::forward<f>(fun)(std::forward<arg>(args)...);
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << (std::chrono::duration_cast<std::chrono::milliseconds>(end - start)).count() << " milisec" << std::endl;
}