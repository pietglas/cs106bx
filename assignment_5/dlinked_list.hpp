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
	Node() {}
	Node(T data, Node<T>* prev, Node<T>* next): 
		data{data}, prev{prev}, next{next} {}
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

	// helper for destructor, copy assignment and extract methods
	T erase(size_t first, size_t last);
	// extract nodes from the list, return the data in the removed node
	T extractFront();
	T extractBack();
	T extractNode(size_t ext_pos);

	// prints the data of the list from front to back
	void print();

private:
	Node<T>* front_ = nullptr;
	Node<T>* back_ = nullptr;
	size_t size_;
};

template<typename T>
DLinkedList<T>::DLinkedList(): size_{0} {}

template<typename T>
DLinkedList<T>::DLinkedList(T data): size_{1} {
	front_ = new Node<T>{data, nullptr, nullptr};
	back_ = front_;
}

template<typename T>
DLinkedList<T>::DLinkedList(const DLinkedList& rhs) {
	if (rhs.getSize() == 0)
		size_ = 0;
	else {
		size_ = rhs.getSize();
		// copy the front node
		front_ = new Node<T>{rhs.getFront(), nullptr, nullptr};
		if (size_ > 1) {
			// copy the nodes between front and back
			size_t pos = 1;
			Node<T>* node = front_;
			while (pos < size_ - 1) {
				node->next = new Node<T>{rhs.getNode(pos), node, nullptr};
				node = node->next;
				++pos;
			}
			// copy the back node 
			node->next = new Node<T>{rhs.getBack(), node, nullptr};
			back_ = node->next;
		}
		else {
			front_->next = nullptr;
			back_ = front_;
		}
	}
}

template<typename T>
T DLinkedList<T>::erase(size_t first, size_t last) {
	T data;
	// start removing from first if that is more efficient
	if (first <= (size_ - last - 1)) {
		// find position
		Node<T>* node = front_;
		size_t pos = 0;
		for (;pos != first; pos++)
			node = node->next;
		// keep track of first node before the ones we are deleting
		Node<T>* keep_node = nullptr;
		if (first != 0) {
			keep_node = node->prev;
			keep_node->next = nullptr;
		}
		// set data
		data = node->data;
		// delete nodes
		for (;pos != last; ++pos) {
			node = node->next;
			delete node->prev;
		}
		// also delete last node. If first node was not the front, 
		// we need to reconnect the nodes.
		if (first != 0) {
			node = node->next;
			delete node->prev;
			keep_node->next = node;
			node->prev = node;
		}
		else if (first == 0 && last != size_ - 1) {
			front_ = node->next;
			node->next->prev = nullptr;
			delete node;
		}
		else {
			delete node;
			front_ = nullptr;
			back_ = nullptr;
		}
	}
	else {
		Node<T>* node = back_;
		size_t pos = size_ - 1;
		for (;pos != last; --pos)
			node = node->prev;
		// delete nodes 
		Node<T>* keep_node = nullptr;
		if (last != size_ - 1) {
			keep_node = node->next;
			keep_node->prev = nullptr;
		}
		// set data
		data = node->data;
		// delete nodes
		for (;pos != first; --pos) {
			node = node->prev;
			delete node->next;
		}
		// also delete first node
		if (last != size_ - 1) {
			node = node->prev;
			delete node->next;
			node->next = keep_node;
			keep_node->prev = node;
		}
		else {
			back_ = node->prev;
			node->prev->next = nullptr;
			delete node;
		}
	}
	size_ -= (last + 1 - first);
	return data;
}

template<typename T>
DLinkedList<T>::~DLinkedList() {
	DLinkedList<T>::erase(0, size_ - 1);
}

// copy assignment. Instead of erasing the list first, we copy the data
// of rhs into the nodes of `*this` as far as we can to avoid calls of `new`
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
				DLinkedList<T>::erase(pos, size_ - 1);
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
	front_ = new Node<T>{data, nullptr, front_};
	if (size_ == 0) 
		back_ = front_;
	else {
		front_->next->prev = front_;
	}
	++size_;
}

template<typename T>
void DLinkedList<T>::addBack(const T& data) {
	back_ = new Node<T>{data, back_, nullptr};
	if (size_== 0) 
		front_ = back_;
	else
		back_->prev->next = back_;
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
		Node<T>* new_node = new Node<T>{data, node->prev, node};
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
	T data = DLinkedList<T>::erase(0, 0);
	return data;
}

template<typename T>
T DLinkedList<T>::extractBack() {
	if (size_ == 0)
		throw std::out_of_range("nothing to extract, list is empty");
	T data = DLinkedList<T>::erase(size_ - 1, size_ - 1);
	return data;
}

template<typename T>
T DLinkedList<T>::extractNode(size_t ext_pos) {
	if (ext_pos >= size_)
		throw std::out_of_range("nothing to extract, out of bounds");
	T data = DLinkedList<T>::erase(ext_pos, ext_pos);
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