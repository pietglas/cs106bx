#include <iostream>
#include <string>
#include <algorithm>	// for std::max()
#include <utility> 		// for std::move()
#include "priority_que_heap.h"
#include "/home/Projects/cs106bx/common_functions.hpp"		// linux directory!

PQueueHeap(): size_{0}, capacity_{10} {
	elts_ = new std::string[capacity_];
}

~PQueueHeap() {
	delete[] elts_;
}

size_t& PQueueHeap::heapifyParentChilds(size_t& pos) {
	if (pos >= size_)
		throw "Out of bounds";

	size_t pos_child1 = 2 * pos + 1;
	size_t pos_child2 =  2 * (pos + 1);
	if (pos_child2 < size_ && elts_[pos] > max(elts_[pos_child1], elts_[pos_child2])) {
		if (elts_[pos_child1] < elts_[pos_child2]) {
			swap(elts_[[pos_child1]], elts_[pos]);
			pos =  pos_child1;
		}

		else {
			swap(elts_[[pos_child2]], elts_[pos]);
			pos =  pos_child2;
		}
	}
	else if (pos_child1 == size_ - 1 && elts_[pos] > elts_[pos_child1]) {
		swap(elts_[pos], elts_[pos_child1]);
		pos = pos_child1;
	}
	return pos;
}

void PQueueHeap::enqueue(const std::string& elem) {
	// if we have reached our maximum capacity, replace our array by a new one,
	// of size 150% of the original one
	if (capacity_ == size_) {
		trash = elts_;
		capacity_ += capacity_ / 2;
		elts_ = new std::string[capacity_];
		for (size_t i = 0; i != size_; i++) 
			elts_[i] = trash[i];
		elts_[size_] = elem;
		delete[] trash;
	}
	else
		elts_[size_] = elem;

	++size_;
	
	// heapify to make the tree complete
	size_t pos = size_;
	while (elts_[pos] < elts_[pos / 2]) {
		swap(elts_[pos], elts_[pos / 2]);
		pos /= 2;
	}

}

std::string PQueueHeap::extractMin() {
	if (size_ == 0)
		throw "The PQueueHeap is empty!";
	std::string first_elt = std::move(elts_[0]);
	// move the last element to the first position, in case they are distinct
	if (size_ > 1)
		elts_[0] = std::move(elts_[size_ - 1]);
	--size_;

	// heapify to obtain a complete tree 
	size_t pos = 0;
	while (elts_[pos] > std::max(elts_[2 * pos + 1], elts_[2 * (pos + 1)])) 
		PQueueHeap::heapifyParentChilds(pos);

	return first_elt;
}

const std::string& PQueueHeap::peek() {
	if (size_ == 0)
		throw "The PQueueHeap is empty!";
	return elts_[0];
}

static PQueueHeap* PQueueHeap::merge(PQueueHeap* one, PQueueHeap* two) {
	if (one->empty() || one == nullptr)
		return two;
	else if (two->empty() || two == nullptr)
		return one;
	else {
		static PQueueHeap* union = new PQueueHeap;
		size_t pos = 0;
		for (; pos != one->size_; pos++)
			union->enqueue(one->elts_[pos]);	// creates new array if we run out of space
		pos = 0;
		for(; pos != two->size_; pos++)
			union->enqueue(two->elts_[pos]);
		union->size_ = (one->size_ * two->size_);
		delete one;
		delete two;

		// heapify

	}
}