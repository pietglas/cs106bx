/* Author: Piet Glas, april 2020. 
 *
 * template class for doubly linked list. A doubly linked list is 
 * composed of nodes. A node contains data of type template<T>, 
 * and pointers to respectively the previous and the next node in 
 * the list to which the current node is supposed to be linked. 
 * The class contains pointers to the nodes at the front and back 
 * of the list as private members.
 *
 * TODO:
 * - add move constructor and move assignment operators
 * - implement copy constructor using recursion
 * - overload boolean comparison operators for Node.
 */

#pragma once

#include <string>
#include <algorithm>		// for std::min()
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
	DLinkedList();
	DLinkedList(T data);
	DLinkedList(const DLinkedList& rhs);
	~DLinkedList();

	DLinkedList& operator =(const DLinkedList& rhs);
	// TODO: add move constructor and move assignment!

	// getters that return the data
	size_t getSize() const;

	const T& getFront() const;
	const T& getBack() const;
	const T& getNode(size_t get_pos) const;

	// returns data, allows data to be changed
	T& setFront();
	T& setBack();
	T& setNode(size_t get_pos);

	// add new node with specified data to the lsit
	void addFront(const T& data);
	void addBack(const T& data);
	void addNode(const T& data, size_t add_pos);

	// extract nodes from the list, return the data in the removed node
	T extractFront();
	T extractBack();
	T extractNode(size_t ext_pos);

	// prints the data of the list from front to back
	void print();

private:
	Node<T>* front_;
	Node<T>* back_;
	size_t size_;
};

template<typename T>
DLinkedList<T>::DLinkedList(): size_{0} {}

template<typename T>
DLinkedList<T>::DLinkedList(T data): size_{1} {
	front_ = new Node<T>;
	front_->data = data;
	front_->prev = nullptr;
	front_->next = nullptr;
	back_ = front_;
}

template<typename T>
DLinkedList<T>::DLinkedList(const DLinkedList& rhs) {
	if (rhs.getSize() == 0)
		size_ = 0;
	else {
		size_ = rhs.getSize();
		// copy the front node
		front_ = new Node<T>;
		front_->data = rhs.getFront();
		front_->prev = nullptr;
		if (size_ > 1) {
			// copy the nodes between front and back
			size_t pos = 1;
			Node<T>* node = front_;
			while (pos < size_ - 1) {
				node->next = new Node<T>;
				node->next->data = rhs.getNode(pos);
				node->next->prev = node;
				node = node->next;
				++pos;
			}
			// copy the back node 
			node->next = new Node<T>;
			back_ = node->next;
			back_->data = rhs.getBack();
			back_->prev = node;
			back_->next = nullptr;
		}
		else {
			front_->next = nullptr;
			back_ = front_;
		}
	}
}

template<typename T>
DLinkedList<T>::~DLinkedList() {
	while (front_->next != nullptr) {
		front_ = front_->next;	// point to the next object
		delete front_->prev;		// delete previous front_ object
	}
	// finally we need to delete object pointed to by back_ = front_
	delete front_;
}

// copy assignment. Maybe a more efficient implementation would be
// to just erase lhs and then copy rhs. 
template<typename T>
DLinkedList<T>& DLinkedList<T>::operator =(const DLinkedList& rhs) {
	if (this != &rhs) {
		size_t pos = 0;
		for (; pos != std::min(size_, rhs.getSize()); pos++)
			DLinkedList::setNode(pos) = rhs.getNode(pos);

		// if the lists have equal size, skip this block
		if (size_ != rhs.getSize()) {
			if (size_ < rhs.getSize()) {
				while (pos < rhs.getSize()) {
					DLinkedList::addBack(rhs.getNode(pos));
					++pos;
				}
			}
			else {
				for (int i = 0; i < size_ - rhs.getSize(); i++)
					DLinkedList::extractNode(pos);
			}
		}
	}
	return *this;
}

// TODO: add move constructor and move assignment!
template<typename T>
size_t DLinkedList<T>::getSize() const {return size_;}

template<typename T>
const T& DLinkedList<T>::getFront() const {
	if (size_ == 0) 
		throw std::out_of_range("Front cannot be changed, list is empty");
	return front_->data;
}

template<typename T>
const T& DLinkedList<T>::getBack() const {
	if (size_ == 0) 
		throw std::out_of_range("Back cannot be changed, list is empty");
	return back_->data;
}

template<typename T>
const T& DLinkedList<T>::getNode(size_t get_pos) const {
	if (get_pos >= size_)
		throw std::out_of_range("nothing here, out of bounds");
	if (get_pos == 0)
		return getFront();
	else if (get_pos == size_ - 1)
		return getBack();
	else {
		Node<T>* node = front_;
		size_t pos = 0;
		while (pos != get_pos) { 
			node = node->next;
			++pos;
		}
		return node->data;
	}
}

template<typename T>
T& DLinkedList<T>::setFront() {
	if (size_ == 0) 
		throw std::out_of_range("Front cannot be changed, list is empty");
	return front_->data;
}

template<typename T>
T& DLinkedList<T>::setBack() {
	if (size_ == 0) 
		throw std::out_of_range("Back cannot be changed, list is empty");
	return back_->data;
}

template<typename T>
T& DLinkedList<T>::setNode(size_t get_pos) {
	if (get_pos >= size_)
		throw std::out_of_range("nothing here, out of bounds");
	if (get_pos == 0)
		return setFront();
	else if (get_pos == size_ - 1)
		return setBack();
	else {
		Node<T>* node = front_;
		size_t pos = 0;
		while (pos != get_pos) { 
			node = node->next;
			++pos;
		}
		return node->data;
	}
}

template<typename T>
void DLinkedList<T>::addFront(const T& data) {
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

template<typename T>
void DLinkedList<T>::addBack(const T& data) {
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

template<typename T>
void DLinkedList<T>::addNode(const T& data, size_t add_pos) {
	if (add_pos > size_)
		throw std::out_of_range("can't add anything here, out of bounds");
	if (size_ == 0 || add_pos == 0) {
		addFront(data);
	}
	else if (add_pos == size_)
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

template<typename T>
T DLinkedList<T>::extractFront() {
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

template<typename T>
T DLinkedList<T>::extractBack() {
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

template<typename T>
T DLinkedList<T>::extractNode(size_t ext_pos) {
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

template<typename T>
void DLinkedList<T>::print() {
	if (size_ == 0)
		throw std::out_of_range("list empty, nothing to print");
	Node<T>* node = front_;
	while (node->next != nullptr) {
		cout << node->data << ", ";
		node = node->next;
	}
	cout << node->data << endl;
}

}	// end namespace adt