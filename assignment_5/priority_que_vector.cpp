#include <vector>
#include <string>
#include "priority_queue_vector.h"
#include <algorithm>

void PQueueVector::enqueue(const std::string& elem) {
	elts_.push_back(elem);
}


std::string PQueueVector::extractMin() {
	if (elts_.empty())
		throw "The vector is empty";
	std::string min_elem = elts_.begin();
	std::vector<std::string>::iterator pos;
	for (auto it = elts_.begin(); it != elts_.end(); it++) {
		if (*it < min_elem) {
			min_elem = *it;
			pos = it;
		}
	}
	elts_.erase(pos);
	return min_elem;
}


const std::string& PQueueVector::peek() {
	if (elts_.empty())
		throw "The vector is empty";
	std::vector<std::string>::iterator pos;
	std::string min_elem = elts_.begin();
	for (auto it = elts_.begin(); it != elts_.end(); it++) {
		if (*it < min_elem) {
			pos = it;
		}
	}
	return *pos;
}


static PQueueVector* PQueueVector::merge(PQueueVector* one, PQueueVector* two) {
	static PQueueVector merged;  // defining a static variable so it stays in scope
	std::merge(one->elts_.begin(), one->elts_.end(),
		two->elts_.begin(), two->elts_.end(), merged.elts_.begin());
	return &merged;
}