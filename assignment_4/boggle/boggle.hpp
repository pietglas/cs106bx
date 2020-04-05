#include <iostream>
#include <complex>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <cmath>

using std::string;
using set_strs = std::set<std::string>;
using vec_strs = std::vector<std::string>;
using vec_chars = std::vector<char>;
using pair = std::pair<int, int>;
using set_pairs = std::set<std::pair<int, int>>;

class Boggle {
public:
	Boggle(bool simple_game = true): simple_game_{simple_game} {
		if (simple_game_) {
			game_size_ = 16;
			rows_ = 4;  
			cols_ = 4;
			cubes_this_game_ = kStandardCubes;
		}
		else {
			game_size_ = 25;
			rows_ = 5;
			cols_ = 5;
			cubes_this_game_ = kBigBoggleCubes;
		}
	}

	void shuffle_cubes();

	void choose_cubes();

	void set_dictionary();

	set_pairs DetermineNeighbors(pair position);

	void SearchWordsPos(std::string& partial_word, pair position, 
		set_pairs neighbors, set_pairs options);

	void SearchWords();

private:
	bool simple_game_;
	unsigned int game_size_;
	unsigned int rows_;
	unsigned int cols_;
	vec_strs cubes_shuffled_;
	vec_chars cubes_chosen_;
	set_strs words_in_game_;
	set_strs dictionary_;
	const string* cubes_this_game_;

	static const string kStandardCubes[16] = {
		"AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
		"AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
		"DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
		"EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
	};
	static const string kBigBoggleCubes[25] = {
		"AAAFRS","AAEEEE","AAFIRS","ADENNN","AEEEEM",
		"AEEGMU","AEGMNN","AFIRSY","BJKQXZ","CCNSTW",
		"CEIILT","CEILPT","CEIPST","DDLNOR","DDHNOT",
		"DHHLOR","DHLNOR","EIIITT","EMOTTT","ENSSSU",
		"FIPRSY","GORRVW","HIPRRY","NOOTUW","OOOTTU"
	};
};

void Boggle::shuffle_cubes() {
	string empty_str = "";
	cubes_shuffled_.resize(game_size_, empty_str);
	for (int i = 0; i != game_size_; i++)
		cubes_shuffled_.at(i) = cubes_this_game_.at(i);
	auto rng = std::default_random_engine {};
	// STL implementation of the Fisher-Yates algorithm
	std::shuffle(cubes_shuffled_.begin(), cubes_shuffled_.end(), rng);
}

void Boggle::choose_cubes() {
	srand(time(nullptr));
	cubes_chosen_.resize(game_size_, "");
	for (int i = 0; i != game_size_; i++) {
		int random_nr = std::rand % game_size_;
		cubes_chosen_.at(i) = cubes_shuffled_[i][random_nr];
	}
}

void set_dictionary() {
	string path_to_dictionary;
	std::getline(cin, path_to_dictionary);
	ifstream dictionary(path_to_dictionary);
	while (!dictionary) {
		std::cout << "Couln't find dictionary, reenter path" << std::endl;
		std::getline(cin, dictionary);
	}
	string new_word;
	while (dictionary >> new_word) 
		dictionary_.emplace(new_word);
}

set_pairs Boggle::DetermineNeighbors(pair position) {
	set_pairs neighbors;
	unsigned int row = position.first;
	unsigned int col = position.second;

	for (int i = std::max(0, row - 1); i != row + 2 && i != rows_; i++) {
		for (int j = std::max(0, col - 1); j != col + 2 && j != cols_; j++) {
			pair neighbor(i, j);
			neighbors.emplace(neighbor);
		}
	}
	return neighbors;	
}

void Boggle::SearchWordsPos(std::string& partial_word, pair position, 
		set_pairs neighbors, set_pairs options) {
	if (!options.empty()) {
		for (auto& new_position : neighbors) {
			// remove this character from the options that we still need
			// to explore
			options.erase(new_position);

			std::string partial_added = 
				partial_word + cubes_chosen_.at(position.first).at(position.second);
			bool keep_looking = false;
			
			// check if we need to continue with this string, by comparing it
			// with the dictionary. 
			for (auto& words : dictionary) {
				if (!words.starts_with(partial_added)) 
					continue;
				else {
					keep_looking = true;
					break;
				}
			}	
			// if there are words starting with our string, continue.
			// else, move on to the next neighbor
			if (keep_looking) {
				// determine new neighbors
				set_pairs new_neighbors = Boggle::DetermineNeighbors(new_position);

				if (partial_added.length >= 4) {
					words_in_game_.emplace(partial_added);
					Boggle::SearchWords(partial_added, new_position, new_neighbors, 
						options, words_in_game_);
				}
				else { // same as above, needs adaption
					Boggle::SearchWords(partial_added, new_position ,new_neighbors,
						options, words_in_game_);
				}
			
			// put position back into posible options, so it can be explored when 
			// starting from another position
			options.emplace(new_position);
			}
		}
	}
}

void Boggle::SearachWords() {
	set_pairs options;
	for (int row = 0; row != rows_; row++) {
		for (int col = 0; col != cols_; col++) {
			pair position(i, j);
			options.emplace(position);
		}
	}

	for (int row = 0; row != rows_; row++) {
		for (int col = 0; col != cols_; col++) {
			pair position(i, j);
			set_pairs neighbors = Boggle::DetermineNeighbors(position);
			string empty_word = "";
			Boggle::SearchWordsPos(empty_word, position, neighbors, options);
		}
	}
}


