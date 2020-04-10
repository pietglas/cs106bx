#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "priority_que.h"

class PQueueVector : public PQueue {
public:
	PQueueVector() {}
	void enqueue(const std::string& elem) override;
	std::string extractMin() override;
	const std::string& peek() override;
	static PQueueVector* merge(PQueueVector* one, PQueueVector* two) override;

private:
	std::vector<std::string> elts_;
}