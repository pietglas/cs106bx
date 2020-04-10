#include<iostream>
#include<string>
#include "priority_que_heap.h"

PQueueHeap(): size_{0}, capacity_{10} {
	elts_ = new std::string[capacity_];
}

~PQueueHeap() {
	delete elts_;
}

void enqueue(const std::string& elem) {
	// if we have reached our maximum capacity, replace our array by a new one,
	// of size 150% of the original one
	if (capacity_ == size_) {
		trash = elts_;
		capacity_ += capacity_ / 2;
		elts_ = new std::string[capacity_];
		for (size_t i = 0; i != size_; i++) 
			elts_[i] = trash[i];
		elts_[size_] = elem;
		delete trash;
	}
	else
		elts_[size_] = elem;
	
	// heapify to make the tree complete
	
}

std::string extractMin();
const std::string& peek();
static PQueueHeap* merge(PQueueHeap* one, PQueueHeap* two);