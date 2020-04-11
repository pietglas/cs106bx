// Interface for several implementations of a priority queue
#pragma once
#include<string>

class PQueue {
public:
	bool empty() {return size_ == 0;}
	const size_t& size() const {return size_;}

	// The following pure virtual members need to be overwritten 
	// by the child classes
	virtual void enqueue(const std::string& elem) = 0;
	virtual std::string extractMin() = 0;
	virtual const std::string& peek() = 0;
	virtual static PQueue* merge(PQueue* one, PQueue* two) = 0;
protected:
	size_t size_;
};