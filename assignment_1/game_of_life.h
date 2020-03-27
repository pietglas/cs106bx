#pragma once

#include <array>

using arr = std::array;

class GameOfLife {
 public:
 	GameOfLife(const int rows, const int cols,
             const std::string& file_name);

    arr<arr<int, cols_>, rows_> state() const {return state_;}

    void PrintState() const;

 	void NextState();

 private:
 	const int rows_;
 	const int cols_;
 	arr<arr<int, cols_>, rows_> state_;
}
