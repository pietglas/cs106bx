#pragma once

#include <string>
#include <stdexcept>
#include <iostream>

using std::cout;	using std::endl;

namespace adt {

template<typename T>
struct Node {
	T data;
	Node<T>* prev;
	Node<T>* next;
};

template<typename T>
class DLinkedList {
public:
	DLinkedList(): size_{0} {};
	DLinkedList(T data): size_{1} {
		front_ = new Node<T>{data, nullptr, nullptr};
		back_ = front_;
	}
	~DLinkedList() {
		while (front_->next != nullptr) {
			front_ = front_->next;	// point to the next object
			delete front_->prev;		// delete previous front_ object
		}
		// finally we need to delete object pointed to by back_ = front_
		delete front_;
	}

	// TODO: add copy constructor, copy assignment and move constructor!

	const T& getFront() const {return front_->data;}

	const T& getBack() const {return back_->data;}

	const T& getNode(size_t get_pos) const {
		if (get_pos >= size_)
			throw std::out_of_range("nothing here, out of bounds");
		Node<T>* node = front_;
		size_t pos = 0;
		while (pos != get_pos) 
			node = node->next;
		return node->data;
	}

	void addFront(const T& data) {
		Node<T>* new_front = new Node<T>;
		// set data
		new_front->data = data;
		new_front->prev = nullptr;
		if (size_ == 0) {
			new_front->next = nullptr;
			front_ = new_front;
			back_ = front_;
		}
		else {
			new_front->next = front_;
			// make it the new front
			front_->prev = new_front;
			front_ = new_front;
		}
		++size_;
	}

	void addBack(const T& data) {
		Node<T>* new_back = new Node<T>;
		new_back->data = data;
		new_back->next = nullptr;
		if (size_== 0) {
			new_back->prev = nullptr;
			front_ = new_back;
			back_ = new_back;
		}
		else {
			new_back->prev = back_;
			back_->next = new_back;
			back_ = new_back;
		}
		++size_;
	}

	void addNode(const T& data, size_t add_pos) {
		if (add_pos > size_)
			throw std::out_of_range("can't add anything here, out of bounds");
		if (size_ == 0 || add_pos == 0) {
			addFront(data);
		}
		else if (add_pos == size_ - 1)
			addBack(data);
		else {
			Node<T>* node = front_;
			size_t pos = 0;
			while (pos != add_pos) {
				node = node->next;
				++pos;
			}
			// make a new node, such that next points to the node which is currently at the 
			// position we want to place the new one, and prev to the previous node. 
			Node<T>* new_node = new Node<T>;
			new_node->data = data;
			new_node->prev = node->prev;
			new_node->next = node;
			// sandwich the newnode between node and node->previous by making their 
			// respective prev and next point to the new node. 
			node->prev->next = new_node;
			node->prev = new_node;
			++size_;		
		}
		
		
	}

	T extractFront() {
		if (size_ == 0)
			throw std::out_of_range("nothing to extract, list is empty");
		Node<T>* get_front = front_;
		if (size_ > 1) {
			front_ = front_->next;
			front_->prev = nullptr;
		}
		T data = get_front->data;
		delete get_front;
		--size_;
		return data;

	}

	T extractBack() {
		if (size_ == 0)
			throw std::out_of_range("nothing to extract, list is empty");
		Node<T>* get_back = back_;
		if (size_ > 1) {
			back_ = back_->prev;
			back_->next = nullptr;
		}
		T data = get_back->data;
		delete get_back;
		--size_;
		return data;
	}

	T extractNode(size_t ext_pos) {
		if (ext_pos >= size_)
			throw std::out_of_range("nothing to extract, out of bounds");
		T data;
		if (ext_pos == 0)
			data = extractFront();
		else if (ext_pos == size_ - 1)
			data = extractBack();
		else {
			Node<T>* node = front_;
			size_t pos = 0;
			while (pos != ext_pos) {
				node = node->next;
				++pos;
			}
			// decouple the node from the list
			node->next->prev = node->prev;
			node->prev->next = node->next;
			data = node->data;
			delete node;
			--size_;
		}
		return data;
	}

	void print() {
		if (size_ == 0)
			throw std::out_of_range("list empty, nothing to print");
		Node<T>* node = front_;
		while (node->next != nullptr) {
			cout << node->data << ", ";
			node = node->next;
		}
		cout << node->data << endl;
	}

private:
	Node<T>* front_;
	Node<T>* back_;
	size_t size_;
};

}	// end namespace adt