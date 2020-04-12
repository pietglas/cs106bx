#include <string>
#include <iostream>
#include "priority_que.h"
#include "priority_que_vector.h"
#include "priority_que_heap.h"

using std::string;
using std::cout;
using std::endl;

int main () {
	pqueue::PQueueHeap* pq = new pqueue::PQueueHeap;
	pqueue::PQueueHeap* pq1 = new pqueue::PQueueHeap;
	string piet = "piet";
	string klaas = "klaas";
	string johan = "johan";
	string martin = "martin";
	pq->enqueue(klaas);
	pq->enqueue(piet);
	pq->enqueue(johan);
	pq->enqueue(martin);
	pq->print();
	string removed = pq->extractMin();
	cout << "removed name: " << removed << endl;
	pq->print();

	string annelies = "annelies";
	string fj = "freerkjan";
	pq1->enqueue(annelies);
	pq1->enqueue(fj);
	string some_name = pq1->peek();
	cout << some_name << endl;
	pqueue::PQueueHeap* pq3 = pqueue::PQueueHeap::merge(pq, pq1);
	pq3->print();


}