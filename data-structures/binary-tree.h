#pragma once
#include <iostream>

template<typename T, typename Allocator = std::allocator<T>, typename Comparator = std::less<T>>
class BinaryTree {
public:
	struct Node;

	Comparator cmp = Comparator();
	using AllocType = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
	AllocType Alc = AllocType();

	BinaryTree() : _size(0), dummy(create_dummy()) {};

	void insert(T&& value) {
		if (dummy->parent == dummy) {
			dummy->parent = create_node(value, dummy);
			dummy->left = dummy->parent;
			dummy->right = dummy->parent;
		}
		else {
			insert_h(dummy->parent, std::move(value));
		}
		_size++;
	}
	
	size_t size() const {
		return _size;
	}

	T left() {
		return (dummy->left->data);
	}

	T right() {
		return (dummy->right->data);
	}

	void print() {
		if (dummy->parent == nullptr) {
			return;
		}
		print_h(dummy->parent);
		std::cout << std::endl;
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

	void insert_h(Node* node, T&& value) {
		if (cmp(value, node->data)) {
			if (node->left == nullptr) {
				node->left = create_node(value, node);
				if (dummy->left == node) {
					dummy->left = node->left;
					node->left = node->right = dummy->left;
				}
			}
			else {
				insert_h(node->left, std::move(value));
			}
		}
		else {
			if (node->right == nullptr) {
				node->right = create_node(std::move(value), node);
				if (dummy->right == node) {
					dummy->right = node->right;
					node->left = node->right = dummy->right;
				}
			}
			else {
				insert_h(node->right, std::move(value));
			}
		}
	}

	void print_h(Node* node) {
		
		if (node->left != nullptr) {
			print_h(node->left);
		}
		if (node->right != nullptr) {
			print_h(node->right);
		}
		std::cout << node->data << ' ';
	}

	Node* create_dummy() {
		Node* dummy = Alc.allocate(1);

		std::allocator_traits<AllocType>::construct(Alc, &(dummy->parent), dummy);
		std::allocator_traits<AllocType>::construct(Alc, &(dummy->left), dummy);
		std::allocator_traits<AllocType>::construct(Alc, &(dummy->right), dummy);

		return dummy;
	}

	Node* create_node(T&& value, Node* parent, Node* left = nullptr, Node* right = nullptr) {
		Node* node = Alc.allocate(1);

		std::allocator_traits<AllocType>::construct(Alc, &(node->data), value);
		std::allocator_traits<AllocType>::construct(Alc, &(node->parent), parent);
		std::allocator_traits<AllocType>::construct(Alc, &(node->left), left);
		std::allocator_traits<AllocType>::construct(Alc, &(node->right), right);

		return node;
	}

	Node* create_node(const T& value, Node* parent, Node* left = nullptr, Node* right = nullptr) {
		return create_node(std::move(T(value)), parent, left, right);
	}


};