#include <vector>
#include <fstream>
#include <iostream>
#include "game_of_life.h"

using GOL = GameOfLife;
using StateVec = std::vector<std::vector<unsigned int>>;

GOL::GameOfLife() {}
GOL::GameOfLife(int rows, int cols, StateVec initial_state):
                rows_{rows}, cols_{cols}, state_{initial_state} {}

bool GOL::ReadInitialState(const std::string& file_name) {
    bool succes = true;
    StateVec initial_state;
    std::ifstream read(file_name);
    if (read) {
        read.ignore(100, '\n');     // ignore first comment
        read >> rows_;
        read >> cols_;
        state_.resize(rows_);
        for (int row = 0; row != rows_; row++) {
            state_[row].resize(cols_);
            for (int col = 0; col != cols_; col++) {
                state_[row][col] = 0;
            }
        }
        int row = 0, col = 0, entry = 0;
        // read initial state from file
        while (read >> entry) {
            initial_state[row][col] = entry;
            col += 1;
            if (col == cols_) {
                row += 1;
                col = 0;
            }
        }
    }
    else {
        std::cout << "Unable to read file, wrong filename maybe?" << std::endl;
        succes = false;
    }
    return succes;
}

void GOL::PrintState() const {
    for (int row = 0; row != rows_; row++) {
        for (int col = 0; col != cols_; col++) {
            std::cout << state_[row][col] << " ";
        }
        std::cout << "" << std::endl;
    }
}

void GOL::NextState() {
	StateVec new_state;
	state_.resize(rows_);
    for (int row = 0; row != rows_; row++) {
        state_[row].resize(cols_);
        for (int col = 0; col != cols_; col++) {
            state_[row][col] = 0;
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
					if ((state_[sub_row][sub_col] != 0) &&
							(sub_col != col || sub_row != row))
						ctr += 1;
				}
			}
			// set new entry according to game rules
			if (ctr == 2) new_state[row][col] = state_[row][col];
			else if (ctr == 3) new_state[row][col] = state_[row][col] + 1;
			else new_state[row][col] = 0;
		}
	}
	state_ = new_state;
}


int main () {
    int cols = 2;
    int rows = 2;
    StateVec initial_state {{1, 1}, {1, 1}};
    GOL game{rows, cols, initial_state};
    game.NextState();
    game.PrintState();
}
