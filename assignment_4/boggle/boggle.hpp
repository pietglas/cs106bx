#pragma once

#include <iostream>
#include <complex>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include "stringmethods.hpp"
#include "game_cubes.hpp"

using std::cout;
using std::endl;
using std::string;
using set_strs = std::set<std::string>;
using vec_strs = std::vector<std::string>;
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
	vec_strs get_cubes_shuffled() const {return cubes_shuffled_;}

	void choose_cubes();
	vec_strs get_sides_chosen() const {return cubes_chosen_;}

	void set_dictionary();

	set_pairs DetermineNeighbors(pair position);

	void SearchWordsPos(std::string& partial_word, pair position, 
		set_pairs neighbors, set_pairs options);

	void find_words();
	set_strs get_words() const {return words_in_game_;}

private:
	bool simple_game_;
	int game_size_;
	int rows_;
	int cols_;
	vec_strs cubes_shuffled_;
	vec_strs cubes_chosen_;
	set_strs words_in_game_;
	set_strs dictionary_;
	const string* cubes_this_game_;
};

void Boggle::shuffle_cubes() {
	string empty_str = "";
	cubes_shuffled_.resize(game_size_, empty_str);
	for (int i = 0; i != game_size_; i++)
		cubes_shuffled_.at(i) = cubes_this_game_[i];
	auto rng = std::default_random_engine {};
	// STL implementation of the Fisher-Yates algorithm
	std::shuffle(cubes_shuffled_.begin(), cubes_shuffled_.end(), rng);
}

void Boggle::choose_cubes() {
	srand(time(nullptr));
	string empty_str = "";
	cubes_chosen_.resize(game_size_, empty_str);
	for (int i = 0; i != game_size_; i++) {
		int random_nr = std::rand() % 6;
		char chosen_side = cubes_shuffled_[i][random_nr];
		char lrcase = std::tolower(chosen_side);
		string side(1, lrcase);
		cubes_chosen_.at(i) = side;
	}
}

void Boggle::set_dictionary() {
	string path_to_dictionary;
	cout << "Enter path to the dictionary: " << endl;
	std::getline(std::cin, path_to_dictionary);
	std::ifstream dictionary(path_to_dictionary);
	while (!dictionary) {
		std::cout << "Couln't find dictionary, reenter path" << std::endl;
		std::getline(std::cin, path_to_dictionary);
		dictionary.open(path_to_dictionary);
	}
	string new_word;
	while (dictionary >> new_word) 
		dictionary_.emplace(new_word);
}

set_pairs Boggle::DetermineNeighbors(pair position) {
	set_pairs neighbors;
	int row = position.first;
	int col = position.second;

	for (int i = std::max(0, row - 1); i != row + 2 && i != rows_; i++) {
		for (int j = std::max(0, col - 1); j != col + 2 && j != cols_; j++) {
			if (i != row || j != col) {
				pair neighbor(i, j);
				neighbors.emplace(neighbor);
			}
		}
	}
	return neighbors;	
}

void Boggle::SearchWordsPos(std::string& partial_word, pair position, 
		set_pairs neighbors, set_pairs options) {
	if (!options.empty()) {
		for (auto& new_position : neighbors) {
			// try next neigbor if the current one is not among remaining options
			if (options.find(new_position) == options.end())
				continue;
			// remove this character from the options that we still need
			// to explore
			options.erase(new_position);

			int array_index = cols_ * new_position.first + new_position.second;
			std::string partial_added = 
				partial_word + cubes_chosen_.at(array_index);
			bool keep_looking = false;
			
			// check if we need to continue with this string, by comparing it
			// with the dictionary. 
			for (auto& word : dictionary_) {
				if (!Prefix(partial_added, word)) 
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

				if (partial_added.length() >= 4 && 
					dictionary_.find(partial_added) != dictionary_.end()) {
					words_in_game_.emplace(partial_added);
					Boggle::SearchWordsPos(partial_added, new_position, new_neighbors, 
						options);
				}
				else { // same as above, needs adaption
					Boggle::SearchWordsPos(partial_added, new_position ,new_neighbors,
						options);
				}
			
			// put position back into posible options, so it can be explored when 
			// starting from another position
			options.emplace(new_position);
			}
		}
	}
}

void Boggle::find_words() {
	set_pairs options;
	for (int row = 0; row != rows_; row++) {
		for (int col = 0; col != cols_; col++) {
			pair position(row, col);
			options.emplace(position);
		}
	}

	for (int row = 0; row != rows_; row++) {
		for (int col = 0; col != cols_; col++) {
			pair position(row,col);
			set_pairs neighbors = Boggle::DetermineNeighbors(position);
			string first_letter = cubes_chosen_.at(row * cols_ + col);
			Boggle::SearchWordsPos(first_letter, position, neighbors, options);
		}
	}
}


