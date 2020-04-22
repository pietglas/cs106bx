// Interface for several implementations of a priority queue

#pragma once
#include<string>

namespace pqueue {

class PQueue {
public:
	PQueue() {}
	PQueue(size_t size): size_{size} {}
	virtual ~PQueue() {}	// 'virtual' prevents undefined behaviour 
	
	bool empty() {return size_ == 0;}
	const size_t size() const {return size_;}

	static PQueue*& merge(PQueue*& one, PQueue*& two) {
		static PQueue* ptr = new PQueue;
		ptr = nullptr;
		return ptr;
	}

	// The following virtual (dummy) members can be overwritten 
	// by the derived classes
	virtual void enqueue(const std::string& elem) {}
	virtual std::string extractMin() {return std::string("");}
	// returning ref to temp object, it's a dummy function anyway
	virtual const std::string& peek() {return std::string("");} 
protected:
	size_t size_;
};

} 	// end namespace pqueue