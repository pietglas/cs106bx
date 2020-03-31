#pragma once

#include <SFML/Graphics.hpp>
#include "grid.hpp"
#include <vector>
using StateVec = std::vector<unsigned int>;

class GameOfLife {
 public:
  GameOfLife(bool simple_game=false);
  
  // setters
  bool read_initial_state(const std::string& file_name);
  void set_tile_set(const std::string& tile_set) {tile_set_ = tile_set;}

  // getters
  int rows() const {return rows_;}
  int cols() const {return cols_;}
  unsigned int& at(const int& row, const int& col) {return state_[row*cols_ + col];}
  StateVec state() const {return state_;}
  Grid grid() const {return grid_;}

	// 'gameplay' members
	void NextState();	
	void DrawGrid();

 private:
 	int rows_ = 0;
 	int cols_ = 0;
 	bool simple_game_ = false;	// cells can age in the default state
 	StateVec state_;
 	std::string tile_set_;
 	Grid grid_;
};
