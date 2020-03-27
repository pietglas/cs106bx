#pragma once

#include <vector>
using StateVec = std::vector<std::vector<unsigned int>>;

class GameOfLife {
 public:
 	GameOfLife();
    GameOfLife(int rows, int cols, StateVec initial_state);

    bool ReadInitialState(const std::string& file_name);

    StateVec state() const {return state_;}

    void PrintState() const;

 	void NextState();

 private:
 	int rows_;
 	int cols_;
 	StateVec state_;
};
