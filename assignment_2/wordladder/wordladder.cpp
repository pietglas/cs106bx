#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <stack>
#include <fstream>

using std::ifstream;
using std::string;
using std::cout;
using std::endl;
using std::cin;
using set_str = std::unordered_set<string>;
using stack_str = std::stack<string>;
using vec_str = std::vector<string>;
using queue_vec_str = std::queue<vec_str>;

// For the function definitions, see the end of the file
set_str CreateDictonary(set_str& empty_dictionary);

stack_str FindOneLetterModifications(const string& word, const set_str& dictionary);

bool InDictionary(const string& word, const set_str& some_dict);

void ExitWhenEmpty(const string& str);

int main() {
	cout << "Welcome to a CS106 ladder application!" << endl;

	// initialize dictionary with english words
	set_str english_dictionary;
	CreateDictonary(english_dictionary);

	cout << "Please enter the source word [return to quit]: " << endl;
	string source_word;
	std::getline(cin, source_word);
	ExitWhenEmpty(source_word);

	while (!InDictionary(source_word, english_dictionary)) {
		cout << "Not an english word, try another word [return to quit]" << endl;
		std::getline(cin, source_word);
		ExitWhenEmpty(source_word);
	}

	cout << " Please enter the destination word "
	" [same amount of letters, return to quit]. " << endl;
	string destination_word;
	std::getline(cin, destination_word);
	ExitWhenEmpty(destination_word);

	while (source_word.length() != destination_word.length()) {
		cout << "Lengths do not match, try again (source word: " << source_word << ")" << endl;
		std::getline(cin, destination_word);
		ExitWhenEmpty(destination_word);
	}

	while (!InDictionary(destination_word, english_dictionary)) {
		cout << "Not an english word, try another word [return to quit]" << endl;
		std::getline(cin, destination_word);
		ExitWhenEmpty(destination_word);
	}

	if (source_word == destination_word) {
		cout << "Found a ladder! " << source_word << " - " << destination_word << endl;
		return 0;
	}

	// initialize some values
	set_str encountered_words;
	vec_str ladder_initializer{source_word};
	queue_vec_str ladders;
	ladders.push(ladder_initializer);

	// do the algorithm as long as we do not find the destination word 
	// in the vector on the front of the queue
	while (((ladders.front()).back() != destination_word)
		&& (!ladders.empty())) {
		// create a stack with all possible one-letter modifications of the 
		// last word on this ladder
		stack_str word_modifications = FindOneLetterModifications((ladders.front()).back(), 
																															english_dictionary);
		
		// a word on the stack is combined with the vector to form a new ladder,
		// if we did not encounter the word before. 
		while (!word_modifications.empty()) {
			vec_str new_ladder = ladders.front();
			string new_word = word_modifications.top();
			// if we did not encounter this word before, add it to make a new ladder
			if (!InDictionary(new_word, encountered_words)) {
				new_ladder.push_back(new_word);
				encountered_words.emplace(new_word);
				ladders.push(new_ladder);
			}
			word_modifications.pop();
		}
		ladders.pop();
	}
	
	// print the found ladder, if any 
	if ((ladders.front()).back() == destination_word) {
		cout << "We found a shortest ladder!" << endl;
		vec_str shortest_ladder = ladders.front();
		for (int i = 0; i != shortest_ladder.size(); i++) {
			cout << shortest_ladder.at(i) << " - ";
		}
		cout << endl;
	}
	else {
		cout << "There is no word ladder connecting " << source_word << " and " 
		<< destination_word << " :(" << endl;
	}
	
	return 0;
}

set_str CreateDictonary(set_str& empty_dictionary) {
	cout << "Enter the path to the dictionary: " << endl;
	string path;
	std::getline(cin, path);
	ifstream file(path);
	while (!file) {
		cout << "Could not open the file, reenter the path" << endl;
		std::getline(cin, path);
		file.open(path);
	}
	string new_word;
	while (file >> new_word)
		empty_dictionary.emplace(new_word);

	return empty_dictionary;
}

stack_str FindOneLetterModifications(const string& word, const set_str& dictionary) {
	stack_str changed_words;
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	for (unsigned int i = 0; i != word.length(); i++) {
		for (auto alph_letter : alphabet) {
			string new_word = word;
			new_word[i] = alph_letter;
			auto it = dictionary.find(new_word);
			if (it != dictionary.end() && new_word != word)
				changed_words.push(new_word);
		}
	}
	return changed_words;
}

bool InDictionary(const string& word, const set_str& some_dict) {
	auto it = some_dict.find(word);
	if (it != some_dict.end())
		return true;
	else
		return false;
}

void ExitWhenEmpty(const string& str) {
	if (str.empty()) {
		cout << "Return pressed, exiting..." << endl;
		exit(0);
	}
}