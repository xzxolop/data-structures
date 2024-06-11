#pragma once

template<typename cont> 
void bubble_sort1(cont& c) {
	size_t cnt = c.size()-1;
	while (cnt > 0) {
		for (size_t i = 0; i < cnt; i++) {
			if (c[i] > c[i + 1]) {
				auto temp = c[i];
				c[i] = c[i + 1];
				c[i + 1] = temp;
			}
		}
		cnt--;
	}
}

template<typename iter>
void bubble_sort2(iter beg, iter end) {
	for (iter i = beg; i != end; i++) {
		for (iter j = beg; j != end-1; j++) {
			if (*j > *(j + 1)) {
				auto temp = *j;
				*j = *(j + 1);
				*(j + 1) = temp;
			}
		}
	}
}