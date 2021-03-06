#include <iostream>
#include <string>
#include "priority_que_dllist.h"
#include "dlinked_list.hpp"
#include "/home/piet/Projects/cs106bx/common_functions.hpp"		// for swap()	// linux directory! 

using std::cout;	using std::endl;
using std::string;

namespace pqueue {

// the following is too slow, we should implement a merge sort algorithm to obtain linear time 
PQueueDLList*& PQueueDLList::merge(PQueueDLList*& one, PQueueDLList*& two) {
	if (one->empty() || one == nullptr)
		return two;
	else if (two->empty() || two == nullptr)
		return one;
	else {
		// if not declared static, the program crashes with segmentation fault
		static PQueueDLList* merged = new PQueueDLList;  // custom copy constructor needed?
		size_t size_one = one->size_;
		size_t size_two = two->size_;
		for (size_t pos = 0; pos < size_one + size_two ; pos++) {
			string elt_one;
			string elt_two;
			if (!one->empty())
				elt_one = one->peek();
			if (!two->empty())
				elt_two = two->peek();
			if (two->empty() || elt_one <= elt_two)
				merged->enqueue(one->extractMin());
			else
				merged->enqueue(two->extractMin());
		}	
		// delete one;		// causes undefined behaviour
		// delete two

		return merged; 
	}
}


// add new string to the list. linear runtime. 
void PQueueDLList::enqueue(const std::string& elem) {
	if (size_ == 0) 
		list_.addFront(elem);
	else {
		if (elem <= list_.getFront())
			list_.addFront(elem);
		else if (elem >= list_.getBack())
			list_.addBack(elem);
		else {
			list_.addBack(elem);
			size_t pos = list_.getSize() - 1;
			while (list_.getNode(pos) < list_.getNode(pos - 1) && pos > 1) {
				commfunc::swap(list_.setNode(pos), list_.setNode(pos - 1));
				--pos;
			}
		}
	}
	size_ = list_.getSize();
}

// remove the element with the highest priority from the list. Constant runtime. 
std::string PQueueDLList::extractMin() {
	string extracted_elt = list_.extractFront();
	size_ = list_.getSize();
	return extracted_elt;
}

// see which element has the highest priority. constant runtime. 
const std::string& PQueueDLList::peek() {
	return list_.getFront();
} 

void PQueueDLList::print() {
	list_.print();
}

}	// end namespace pqueue