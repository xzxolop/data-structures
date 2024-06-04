#pragma once
#include <iostream>

template<typename T, typename Allocator = std::allocator<T>, typename Comparator = std::less<T>>
class BinaryTree {
public:
	struct Node;

	BinaryTree() : _size(0), dummy(new Node(T())) {};
	Comparator cmp = Comparator();

	void insert(T&& value) {
		if (dummy->parent == nullptr) {
			dummy->parent = new Node(value);
		}
		else {
			insert_h(dummy->parent, value);
		}
	}

	void insert_h(Node* node, T value) {
		if (cmp(value, node->data)) {
			if (node->left == nullptr) {
				node->left = new Node(value);
			}
			else {
				insert_h(node->left, value);
			}
		}
		else {
			if (node->right == nullptr) {
				node->right = new Node(value);
			}
			else {
				insert_h(node->right, value);
			}
		}
	}

	void print() {
		if (dummy->parent == nullptr) {
			return;
		}
		print_h(dummy->parent);
	}

private:
	struct Node {
	public:
		T data;
		Node* parent;
		Node* left;
		Node* right;

		Node(const T& value = T(), Node* p = nullptr, Node* l = nullptr, Node* r = nullptr) : data(value), parent(p), left(l), right(r) {};
		Node(const T&& value = std::move(T()), Node* p = nullptr, Node* l = nullptr, Node* r = nullptr) : data(std::move(value)), parent(p), left(l), right(r) {};
	};

	Node* dummy;
	size_t _size;

	void print_h(Node* node) {
		
		if (node->left != nullptr) {
			print_h(node->left);
		}
		if (node->right != nullptr) {
			print_h(node->right);
		}
		std::cout << node->data << ' ';
	}

};