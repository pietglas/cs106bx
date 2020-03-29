#pragma once

#include <vector>
using StateVec = std::vector<unsigned int>;

class GameOfLife {
 public:
  GameOfLife();
  GameOfLife(int rows, int cols);
  GameOfLife(int rows, int cols, StateVec initial_state);

  bool ReadInitialState(const std::string& file_name);

  // getters
  int rows() const {return rows_;}
  int cols() const {return cols_;}
  unsigned int& at(const int& row, const int& col) {return state_[row*cols_ + col];}
  StateVec state() const {return state_;}

  void PrintState() const;

	void NextState();

 private:
 	int rows_;
 	int cols_;
 	StateVec state_;
};
