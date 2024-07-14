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
	
	size_t size() const noexcept {
		return _size;
	}

	T left() const noexcept {
		return (dummy->left->data);
	}

	T right() const noexcept {
		return (dummy->right->data);
	}

	void print_lnr(const std::string& devider = " ") const {
		if (dummy->parent == nullptr) {
			return;
		}
		print_lnr(dummy->parent, devider);
		std::cout << std::endl;
	}

	void print_rnl(const std::string& devider = " ") const {
		if (dummy->parent == nullptr) return;
		std::vector<Node*> stack;
		Node* current = dummy->parent; 
		stack.push_back(current);
		while (stack.size() > 0 && current != nullptr) {
			while (current != dummy && current != nullptr)
			{
				stack.push_back(current);
				current = current->left;
			}
			if (stack.size() > 0) {
				current = stack[stack.size() - 1];
				stack.pop_back();
				std::cout << current->data << devider;
				current = current->right;
			}
			std::cout << stack.size();
		}
		std::cout << std::endl;

		/*for (auto i = stack.end() - 1; i > stack.begin(); i--) {
			std::cout << *i << devider;
		}
		std::cout << std::endl;*/
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
		if (cmp(value, node->data)) { // if insert elem < root
			if (node->left == nullptr) {
				node->left = create_node(value, node);
				if (dummy->left == node) { // if value - most left elem, then pointer on most left elem changed
					dummy->left = node->left;
					node->left = node->right = dummy->left;
				}
			}
			else { // if not find place for insert
				insert_h(node->left, std::move(value)); 
			}
		}
		else { // if insert elem > root
			if (node->right == nullptr) {
				node->right = create_node(std::move(value), node);
				if (dummy->right == node) { // if value - most right elem, then pointer on most right elem changed
					dummy->right = node->right;
					node->left = node->right = dummy->right;
				}
			}
			else { // if not find place for insert
				insert_h(node->right, std::move(value));
			}
		}
	}

	void print_lnr(Node* node, const std::string& devider = " ") const {
		
		if (node->left != nullptr) {
			print_lnr(node->left, devider);
		}
		else if (node->right != nullptr) {
			print_lnr(node->right, devider);
		}
		std::cout << node->data << devider;
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