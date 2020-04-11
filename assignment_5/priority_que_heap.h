#pragma once
#include<string>
#include "priority_que.h"

class PQueueHeap : public PQueue {
public:
	PQueueHeap();
	~PQueueHeap();			// should also define copy constructor & copy assignment

	void enqueue(const std::string& elem) override;
	std::string extractMin() override;
	const std::string& peek() override;
	PQueueHeap* merge(PQueueHeap* one, PQueueHeap* two);
private:
	std::string* elts_;
	size_t capacity_;
	size_t& heapifyParentChilds(size_t& pos);
};