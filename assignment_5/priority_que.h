// Interface for several implementations of a priority queue
#pragma once
#include<string>

class PQueue {
public:
	virtual void enqueue(const std::string& elem) = 0;
	virtual std::string extractMin() = 0;
	virtual const std::string& peek() = 0;
	virtual static PQueue* merge(PQueue* one, PQueue* two) = 0;
};