#include <string>
#include <iostream>
#include "priority_que.h"
#include "priority_que_vector.h"
#include "priority_que_heap.h"
#include "dlinked_list.hpp"
#include "/home/piet/Projects/cs106bx/common_functions.hpp"		// linux directory!

using std::string;
using std::cout;
using std::endl;

int main () {
	adt::DLinkedList<int> lijst;
	lijst.addFront(1);
	lijst.addBack(3);
	lijst.addNode(2, 1);
	lijst.print();
	lijst.extractFront();
	cout << "extracted front member" << endl;
	lijst.print();
	lijst.extractBack();
	cout << "extracted back member" << endl;
	lijst.print();
	lijst.addNode(0, 0);
	cout << "added 0" << endl;
	lijst.extractNode(1);
	cout << "removed something from position 1" << endl;
	lijst.print();
	adt::DLinkedList<int> lust = lijst;
	cout << "Created a new list from another one" << endl;
	lust.print();
	lust.addNode(1, 1);
	cout << "added 1 to back of lust" << endl;
	lust.print();
	lust.setNode(1) = 2;
	lust.print();
	lijst = lust;
	cout << "copied lijst from lust" << endl;
	lijst.print();
	lijst.addBack(3);
	cout << "added " << lijst.getBack() << " to back of lijst" << endl;
	cout << "the size of lijst is " << lijst.getSize() << endl;
	lijst.print();
	lijst = lust;
	lijst.print();
	commfunc::swap(lijst.setNode(0), lijst.setNode(1));
	lijst.print();





	/*****Test instances for PQueueHeap*****/

	// pqueue::PQueueHeap* pq = new pqueue::PQueueHeap;
	// pqueue::PQueueHeap* pq1 = new pqueue::PQueueHeap;
	// string piet = "piet";
	// string klaas = "klaas";
	// string johan = "johan";
	// string martin = "martin";
	// pq->enqueue(klaas);
	// pq->enqueue(piet);
	// pq->enqueue(johan);
	// pq->enqueue(martin);
	// pq->print();
	// string removed = pq->extractMin();
	// cout << "removed name: " << removed << endl;
	// pq->print();

	// string annelies = "annelies";
	// string fj = "freerkjan";
	// pq1->enqueue(annelies);
	// pq1->enqueue(fj);
	// string some_name = pq1->peek();
	// cout << some_name << endl;
	// pqueue::PQueueHeap* pq3 = pqueue::PQueueHeap::merge(pq, pq1);
	// pq3->print();

	// pqueue::PQueueHeap pq4;
	// pq4.peek();

}