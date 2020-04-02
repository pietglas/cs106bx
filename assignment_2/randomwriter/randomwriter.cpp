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
using std::queue;
using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using gram_map = map<queue<string>, vector<string>>;

gram_map CreateNGrams(ifstream& file, const unsigned int& size) {
	// position the queue at the beginning of the file
	gram_map n_grams;
	queue<string> key;
	for (int position = 0; position != size; position++) {
		string word;
		file >> word;
		key.push(word);
	}

	// loop over the file, repositioning the windows one position at a time
	string new_word;
	while (file >> new_word) {
		vector<string> value{new_word};
		// modify the value, if the key already has one
		if (!n_grams.try_emplace(key, value).second)
			n_grams.at(key).push_back(new_word);
		key.pop();
		key.push(new_word);
	}
	return n_grams;
}

void GenerateRandomText(ifstream& file, ofstream& output, unsigned int wordcount,
						gram_map grams, int gramsize, const unsigned int& length) {
	// generate the key to start with, write it to output file
    queue<string> key;
    for (int j = 0; j != gramsize; j++) {
        string word;
        file >> word;
        key.push(word);
        output << word;
    }

    // randomly select a string from this value and write it to the file
    for (int words_written = 0; words_written != length; words_written++) {
        vector<string> value = grams.at(key);
        unsigned int random_pos = rand() & (value.size() - 1);
        cout << "random chosen position: " << random_pos << endl;
        string random_word = value.at(random_pos);
        output << random_word;

        // modify the key for the next iteration
        string new_word;
        if (!(file >> new_word)) {
            cout << "Reached end of document." << endl;
            break;
        }
        key.pop();
        key.push(new_word);
    }

}



int main() {
	srand(time(nullptr)); // as not to get the same number every time

	// Open file #1: count nr of words 
	string file_name = "sentence.txt";
	ifstream file(file_name);
	while (!file) {
		cout << "Unable to open file, try again: ";
		std::getline(std::cin, file_name);
		file.open(file_name);
	}
	std::istream_iterator<string> in{file}, end;
	unsigned int wordcount = std::distance(in, end);
	file.close();
	
	// Open file #2: get the N-grams
	ifstream samefile(file_name);
	while (!samefile) {
		cout << "Unable to open file, try again: ";
		std::getline(std::cin, file_name);
		samefile.open(file_name);
	}
    int gramsize = 2;
    gram_map grams = CreateNGrams(samefile, gramsize);
    samefile.close();

    // Open file to which the output will be written
    ofstream output("randomtext.txt");
	if (!output) {
        cout << "could not open a new file, sorry!" << endl;
        exit(1);
	}

    // Open file #3: get random position in the file
    ifstream file3(file_name);
	while (!file3) {
		cout << "Unable to open file, try again: ";
		std::getline(std::cin, file_name);
		file3.open(file_name);
	}
	std::istream_iterator<string> start{file3}, eof;
	std::istream_iterator<string> iter = in;
	int pos = std::rand() % (wordcount - gramsize - 1);
	for (int i = 0; i != pos; i++) {
        ++start;
	}

    GenerateRandomText(file3, output, wordcount, grams, gramsize, 5);

    file3.close();
    output.close();
}	
