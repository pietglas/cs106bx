#include <vector>
#include <string>
#include "priority_que_vector.h"
#include <algorithm>

namespace pqueue {

void PQueueVector::enqueue(const std::string& elem) {
	elts_.push_back(elem);
}


std::string PQueueVector::extractMin() {
	if (elts_.empty())
		throw "The vector is empty";
	std::string min_elem = elts_.at(0);
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
	std::string min_elem = elts_.at(0);
	for (auto it = elts_.begin(); it != elts_.end(); it++) {
		if (*it < min_elem) {
			pos = it;
		}
	}
	return *pos;
}


PQueueVector* PQueueVector::merge(PQueueVector* one, PQueueVector* two) {
	static PQueueVector* merged = new PQueueVector;  // defining a static variable so it stays in scope
	std::merge(one->elts_.begin(), one->elts_.end(),
		two->elts_.begin(), two->elts_.end(), std::back_inserter(merged->elts_));
	delete one;
	delete two;
	return merged;
}

}	// end namespace pqueue