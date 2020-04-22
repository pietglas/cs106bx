/* Contains declaration of a priority queue, implemented as a 
 * binary heap: a binary tree that is complete, i.e. can be
 * represented as an array (and it is implemented as such).
 * Additionally, it has the heap property: childrens are >= than their parent. 
 * Performance: enqueue is O(1), peek and extractmin are O(logn), and merge
 * runs O(n). 
 */

#pragma once
#include <string>
#include "priority_que.h"

namespace pqueue {

class PQueueHeap : public PQueue {
public:
	PQueueHeap();
	~PQueueHeap();			// should also define copy constructor & copy assignment

	void enqueue(const std::string& elem) override;
	std::string extractMin() override;
	const std::string& peek() override;
	static PQueueHeap*& merge(PQueueHeap*& one, PQueueHeap*& two);

	void print();			// only there for debugging purposes
private:
	std::string* elts_;
	size_t capacity_;
	size_t& heapifyParentChilds(size_t& pos);
	void heapify(size_t& pos);
};

} 	// end namespace pqueue