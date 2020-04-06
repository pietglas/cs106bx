#include <iostream>
#include <complex>
#include <string>
#include <set>
#include "boggle.hpp"

using std::cout;
using std::endl;
using std::string;
using set_strs = std::set<std::string>;
using vec_strs = std::vector<std::string>;
using pair = std::pair<int, int>;
using set_pairs = std::set<std::pair<int, int>>;

set_strs found_words;


int main() {
	// set the game
	Boggle boggle{true};
	boggle.shuffle_cubes();
	boggle.choose_cubes();
	boggle.set_dictionary();
	boggle.find_words();

	// view the initial game state
	vec_strs cubes_shuffled = boggle.get_cubes_shuffled();
	vec_strs sides_chosen = boggle.get_sides_chosen();
	set_strs words_found = boggle.get_words();

	int ctr = 0;
	for (auto& cube : cubes_shuffled) {
		cout << cube << " ";
		ctr++;
		if (ctr == 4) {
			cout << endl;
			ctr = 0;
		}
	}



	ctr = 0;
	for (auto& letter : sides_chosen) {
		cout << letter << " ";
		ctr++;
		if (ctr == 4) {
			cout << endl;
			ctr = 0;
		}
	}



	for (auto& word : words_found) 
		cout << word << endl;

}	