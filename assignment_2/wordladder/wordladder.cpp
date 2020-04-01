#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <stack>
#include <fstream>

using ifstream = std::ifstream
using string = std::string
using set_str = std::unordered_set<string>
using stack_str = std::stack<string>
using cout = std::cout
using endl = std::endl
using vec_str = std::vector<string>
using queue_vec_str = std::queue<vec_str>

// function that generates a stack containing all words differing one character
// from the parameter 

set CreateDictonary() {
	cout << "Enter the path to the dictionary: " << endl;
	string path;
	cin >> path;
	ifstream file;
	while (!(file.open(path))) {
		cout << "Could not open the file, reenter the path" << endl;
		cin >> path;
		file.open(path);
	}
	set dictionary;
	string new_word;
	while (file >> new_word)
		set.emplace(new_word);

	return dictionary;
}

stack_str ChangeLetter(const string& word, const set& dictionary) {
	stack_str changed_words;
	string alphabet = "abcdefghijklmnopqrstuvwxyz"
	for (unsigned int i = 0; i != word.length(); i++) {
		for (auto alph_letter : alphabet) {
			string new_word = word;
			new_word[i] = alph_letter;
			auto it = dictionary.find(new_word);
			if (it != dictionary.end() && new_word != word)
				stack.push(new_word);
		}
	}
	return changed_words;
}


int main() {
	cout << "Welcome to a CS106 ladder application!" << endl;
	cout << "Please enter the source word [return to quit]: " << endl;
	string source_word;
	cin >> source_word;
	if (source_word == "") {
		cout << "Exiting.. " << endl;
		return 0;
	}

	cout << " Please enter the destination word "
	" [same amount of letters, return to quit]. " << endl;
	string destination_word;
	cin >> destination_word;
	while (source_word.length() != destination_word.lengt()) {
		cout << "Lengths do not match, try again (source word: " << source_word << ")" << endl;
		cin.ignore();
		cin >> destination_word;
	}

	if (source_word == destination_word) {
		cout << "Found a ladder! " << source_word << " - " << destination_word << endl;
		return 0;
	}

	// initialize some values
	set encountered_words{};
	set dictionary = CreateDictionary();
	queue_vec_str ladders = {{source_word}};

	// do the algorithm as long as we do not find the destination word 
	// in the vector on the front of the queue
	while (ladders.front()[ladders.front().back()] != destination_word) {
		// take the last element of the vector and create a stack with
		// all possible one-letter modifications
		string last_word = ladders.front()[ladders.front().back()];
		stack_str word_modifications = ChangeLetter(last_word);
		
		// a word on the stack is combined with the vector to form a new ladder,
		// if we did not encounter the word before. 
		while (word_modifications.empty() == false) {
			vec_str new_ladder = ladders.front();
			string new_word = word_modifications.top();
			auto it = encountered_words.find(new_word);
			if (it == encountered_words.end()) {
				new_ladder.push_back(new_word);
				ladders.push(new_ladder);
			}
			word_modifications.pop();
		}
		ladders.pop();
	}
	cout << " "

}