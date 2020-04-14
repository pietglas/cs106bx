#include <iostream>
#include <string>
#include <algorithm>	// for std::max()
#include <utility> 		// for std::move()
#include <stdexcept>
#include "priority_que_heap.h"
#include "/home/piet/Projects/cs106bx/common_functions.hpp"		// linux directory!

using std::cout;	using std::endl;

namespace pqueue {

PQueueHeap::PQueueHeap(): PQueue(0), capacity_{10} {
	elts_ = new std::string[capacity_];
}

PQueueHeap::~PQueueHeap() {
	delete[] elts_;
}

size_t& PQueueHeap::heapifyParentChilds(size_t& pos) {
	size_t pos_child1 = 2 * pos + 1;
	size_t pos_child2 =  2 * (pos + 1);
	if (pos_child2 < size_ && elts_[pos] > std::min(elts_[pos_child1], elts_[pos_child2])) {
		if (elts_[pos_child1] < elts_[pos_child2]) {
			commfunc::swap(elts_[pos_child1], elts_[pos]);
			pos =  pos_child1;
		}

		else {
			commfunc::swap(elts_[pos_child2], elts_[pos]);
			pos =  pos_child2;
		}
	}
	else if (pos_child1 == size_ - 1 && elts_[pos] > elts_[pos_child1]) {
		commfunc::swap(elts_[pos], elts_[pos_child1]);
		pos = pos_child1;
	}
	return pos;
}

// pushes the root down to obtain a heap. Assumes that the children are
// the roots of heaps. 
void PQueueHeap::heapify(size_t& pos) {
	size_t old_pos = pos;
	size_t new_pos = pos;
	if (pos < size_) {
		do {
			old_pos = pos;
			new_pos = PQueueHeap::heapifyParentChilds(pos);		// updates pos
		} while (pos < size_ && old_pos != new_pos);
	}
}

void PQueueHeap::enqueue(const std::string& elem) {
	// if we have reached our maximum capacity, replace our array by a new one,
	// of size 150% of the original one
	if (capacity_ == size_) {
		std::string* trash = elts_;
		capacity_ += capacity_ / 2;
		elts_ = new std::string[capacity_];
		for (size_t i = 0; i != size_; i++) 
			elts_[i] = trash[i];
		elts_[size_] = elem;
		delete[] trash;
	}
	else {
		elts_[size_] = elem;
	}

	++size_;
	
	// heapify to make the tree complete
	size_t pos = size_ - 1;
	while (elts_[pos] < elts_[pos / 2]) {
		commfunc::swap(elts_[pos], elts_[pos / 2]);
		pos /= 2;
	}

}

std::string PQueueHeap::extractMin() {
	if (size_ == 0)
		throw std::out_of_range("the priority queue is empty");	// doesn't show
	std::string first_elt = std::move(elts_[0]);
	// move the last element to the first position, in case they are distinct
	if (size_ > 1)
		elts_[0] = std::move(elts_[size_ - 1]);
	--size_;

	// heapify to obtain a complete tree 
	size_t pos = 0;
	PQueueHeap::heapify(pos);

	return first_elt;
}

const std::string& PQueueHeap::peek() {
	if (size_ == 0)
		throw std::out_of_range("the priority queue is empty");	
	return elts_[0];
}

// The following is flawed, since enqueueing does already make sure that the order is right!
PQueueHeap*& PQueueHeap::merge(PQueueHeap*& one, PQueueHeap*& two) {
	if (one->empty() || one == nullptr)
		return two;
	else if (two->empty() || two == nullptr)
		return one;
	else {
		// if not declared static, the program crashes with segmentation fault
		static PQueueHeap* merged = new PQueueHeap;  // custom copy constructor needed?
		merged->size_ = (one->size_ + two->size_);
		merged->elts_ = new std::string[merged->size_];
		for (size_t pos = 0; pos != one->size_; pos++) {
			merged->elts_[pos] = one->elts_[pos];	// creates new array if we run out of space
			cout << "Added element " << merged->elts_[pos] << endl;
		}
		for(size_t pos1 = one->size_; pos1 != merged->size_; pos1++) {
			merged->elts_[pos1] = two->elts_[pos1 - one->size_];
			cout << "Added element " << merged->elts_[pos1] << endl;
		}
		
		delete one;
		delete two;

		// heapify. The first node must be heapified outside of the for-loop, since we're
		// working with unsigned integers. 
		size_t i = merged->size_ - 1;
		for (; i != 0; i--) 
			merged->heapify(i);
		i = 0;
		merged->heapify(i);		

		return merged; 
	}
}

void PQueueHeap::print() {
	cout << "The queue has size: " << size_ << endl;
	for (int i = 0; i != size_; i++)
		cout << elts_[i] << ", ";
	cout << endl;
}

}	// end namespace pqueue