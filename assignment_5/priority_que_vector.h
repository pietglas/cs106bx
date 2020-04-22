/* Priority queue implemented on the basis of std::vector. 
 * Performance: enqueue is O(1), the others are are O(n)
 */

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "priority_que.h"

namespace pqueue {

class PQueueVector : public PQueue {
public:
	PQueueVector() {}
	~PQueueVector() {} 		
	void enqueue(const std::string& elem) override;
	std::string extractMin() override;
	const std::string& peek() override;
	PQueueVector* merge(PQueueVector* one, PQueueVector* two);

private:
	std::vector<std::string> elts_;
};

} 	// end namespace pqueue