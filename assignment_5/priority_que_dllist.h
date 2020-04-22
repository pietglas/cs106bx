/* Priority queue implemented on the basis of a doubly linked list, see
 * dlinked_list.hpp for the implementation of a doubly linked list. 
 * Performance: extractMin and peek are O(1), enqueue and merge are O(n).
 */ 

#pragma once
#include<string>
#include "dlinked_list.hpp"
#include "priority_que.h"

namespace pqueue {

class PQueueDLList : public PQueue {
public:
	PQueueDLList() {}
	~PQueueDLList() {}

	static PQueueDLList*& merge(PQueueDLList*& one, PQueueDLList*& two);

	void enqueue(const std::string& elem) override;
	std::string extractMin() override;
	const std::string& peek() override; 

	void print();		// for debugging purposes
private:
	adt::DLinkedList<std::string> list_;
};

} 	// end namespace pqueue