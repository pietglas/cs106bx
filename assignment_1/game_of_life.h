#pragma once

#include <array>

using arr = std::array;

class GameOfLife {
 public:
 	GameOfLife(const int rows, const int cols, std::string file_name);
 	
 	arr<arr<int, cols_>, rows_> NextState();

 private:
 	const int rows_;
 	const int cols_;
 	std::array<std::array<int, cols_>, rows_> old_array, new_array;
}