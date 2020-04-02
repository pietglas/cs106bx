#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>
using namespace std;
using gram_map = map<queue<string>, vector<string>>;

int main() {
	string file_name = "sentence.txt";
	ifstream file(file_name);
	while (!file) {
		cout << "Unable to open file, try again: ";
		std::getline(cin, file_name);
		file.open(file_name);
	}

	istream_iterator<string> in{file}, end;
	istream_iterator<string> iter = in;
	cout << *in << ", " << endl;
	for (int i = 0; i != 6; i++) {
		 ++iter;
	}
	cout << *iter << endl;
	cout << "Word count: " << distance(in, end) << endl;

}
