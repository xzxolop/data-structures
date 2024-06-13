#pragma once

template<typename cont>
void bubble_sort_alik(cont& c) {
	size_t len = c.size();
	while (len != 0) {
		size_t max_ind = 0;
		for (size_t i = 1; i < len; i++) {
			if (c[i - 1] > c[i]) {
				std::swap(c[i - 1], c[i]);
				max_ind = i;
			}
		}
		len = max_ind;
	}
}

template<typename cont>
void bubble_sort(cont& c) {
	size_t cnt = c.size() - 1;
	while (cnt > 0) {
		for (size_t i = 0; i < cnt; i++) {
			if (c[i] > c[i + 1]) {
				std::swap(c[i], c[i + 1]);
			}
		}
		cnt--;
	}
}


template<typename iter>
void bubble_sort(iter beg, iter end) {
	for (iter i = beg; i != end; i++) {
		for (iter j = beg; j != end - (i - beg) - 1; j++) {
			if (*j > *(j + 1)) {
				std::swap(*j, *(j + 1));
			}
		}
	}
}