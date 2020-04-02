#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <cstdlib>

using std::map;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using gram_map = map<queue<string>, vector<string>>;

gram_map CreateNGrams(ifstream& file, const unsigned int& size) {
	// position the queue at the beginning of the file
	gram_map n_grams;
	queue<string> window;
	for (int position = 0; position != size; position++) {
		string word;
		file >> word;
		window.push(word);
	}

	// loop over the file, repositioning the windows one position at a time
	string new_word;
	while (file >> new_word) {
		vector<string> value{new_word};
		// modify the value, if the key already has one 
		if (!n_grams.try_emplace(window, value).second) 
			n_grams.at(window).push_back(new_word);
		window.pop();
		window.push(new_word);
	}
	return n_grams;
}

void GenerateRandomText(ifstream& file, ofstream& output, 
						const unsigned int& gramsize, const unsigned int& length) {
	// find the number of words in the file
	std::istream_iterator<string> in{file}, end;
	int wordcount = std::distance(in, end);

	// randomly position the ifstream at some point in the text
	unsigned int position = rand() % (wordcount - gramsize);
	std::istream_iterator<string> in + position;
}

int main() {
	gram_map grams;
	string file_name = "../sentence.txt";
	ifstream file(file_name);
	while (!file) {
		cout << "Unable to open file, try again: "; 
		std::getline(cin, file_name);
		file.open(file_name);	
	}
	grams = CreateNGrams(file, 2);

	for (auto& key_val:grams) {
		queue<string> key = key_val.first;
		cout << "KEY: ";
		for (int i = 0; i != key.size(); i++) {
			string front = key.front();
			cout << front << " ";
			key.pop();
			key.push(front);
		}
		vector<string> val = key_val.second;
		cout << "VALUE: ";
		for (auto it = val.begin(); it != val.end(); ++it) {
			cout << *it << ", ";
		}
		cout << endl;
	}
}

