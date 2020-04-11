#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "priority_que.h"

class PQueueVector : public PQueue {
public:
	PQueueVector() {}
	virtual ~PQueueVector() {} 		// 'virtual' prevents undefined behaviour 
	void enqueue(const std::string& elem) override;
	std::string extractMin() override;
	const std::string& peek() override;
	PQueueVector* merge(PQueueVector* one, PQueueVector* two);

private:
	std::vector<std::string> elts_;
};