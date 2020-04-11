pragma once
#include<string>

class PQueueHeap : public PQueue {
public:
	PQueueHeap();
	~PQueueHeap();			// should also define copy constructor & copy assignment

	void enqueue(const std::string& elem);
	std::string extractMin();
	const std::string& peek();
	static PQueueHeap* merge(PQueueHeap* one, PQueueHeap* two);
private:
	string* elts_;
	size_t capacity_;
	void heapifyParentChilds(size_t pos);
};