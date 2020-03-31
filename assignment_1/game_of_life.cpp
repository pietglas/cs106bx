#include <vector>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include "game_of_life.h"

// add sleep function for windows/linux
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using GOL = GameOfLife;
using StateVec = std::vector<unsigned int>;

GOL::GameOfLife(bool simple_game): simple_game_{simple_game} {}

// Read the initial state of the game from a text file
bool GOL::read_initial_state(const std::string& file_name) {
  bool succes = true;
  std::ifstream read(file_name);
  if (read) {
    read.ignore(100, '\n');     // ignore first comment
    read >> rows_;
    read >> cols_;
    state_.reserve(rows_ * cols_);
    int entry = 0;
    // read initial state from file
    while (read >> entry) {
      state_.push_back(entry);
    }
  }
  else {
    std::cout << "Unable to read file, wrong filename maybe?" << std::endl;
    succes = false;
  }
  return succes;
}

// calculate the next state, according to the game rules
void GOL::NextState() {
	StateVec new_state;
	new_state.reserve(rows_ * cols_);
  for (int row = 0; row != rows_; row++) {
      for (int col = 0; col != cols_; col++) {
          new_state.push_back(0);
      }
  }
	for (int row = 0; row != rows_; row++) {
		for (int col = 0; col != cols_; col++) {
			int ctr = 0;
			// count how many neighbors are nonempty
			for (int sub_row = std::max(0, row - 1);
					sub_row != row + 2 && sub_row != rows_; sub_row++) {
				for (int sub_col = std::max(0, col - 1);
						sub_col != col + 2 && sub_col != cols_; sub_col++) {
					if ((state_[sub_row*cols_ + sub_col] != 0) &&
							(sub_col != col || sub_row != row))
						ctr += 1;
				}
			}
			// set new entry according to game rules
      if (simple_game_ == false) {
			  if (ctr == 2 && state_[row*cols_ + col] != 0) 
          new_state[row*cols_ + col] = state_[row*cols_ + col] + 1;
			  else if (ctr == 3) 
          new_state[row*cols_ + col] = state_[row*cols_ + col] + 1;
			  else 
          new_state[row*cols_ + col] = 0;
      }
      
      // set the scenario where cells don't age
      else {
        if (ctr == 2 && state_[row*cols_ + col] != 0) 
          new_state[row*cols_ + col] = 1;
        else if (ctr == 3) 
          new_state[row*cols_ + col] = 1;
        else 
          new_state[row*cols_ + col] = 0;
      }
		}
	}
	state_ = new_state;
}

void GOL::DrawGrid() {
  while (!grid_.load(tile_set_, 
    sf::Vector2u(32, 32), state_, rows_, cols_)) {
    std::cout << "Unable to open file, reenter path" << std::endl;
    cin.clear();
    cin.ignore();
    cin >> tile_set_;
    grid_.load(tile_set_, sf::Vector2u(32, 32), state_, rows_, cols_);
  }
}
