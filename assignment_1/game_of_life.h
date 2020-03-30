#pragma once

#include <vector>
using StateVec = std::vector<unsigned int>;

class GameOfLife {
 public:
  GameOfLife(bool simple_game=false);
  bool ReadInitialState(const std::string& file_name);

  // getters
  int rows() const {return rows_;}
  int cols() const {return cols_;}
  unsigned int& at(const int& row, const int& col) {return state_[row*cols_ + col];}
  StateVec state() const {return state_;}

	// 'gameplay' members
	void NextState();		

 private:
 	int rows_ = 0;
 	int cols_ = 0;
 	bool simple_game_ = false;	// cells can age in the default state
 	StateVec state_;
};
