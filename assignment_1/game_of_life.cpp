#include <array>
#include <fstream>
#include "game_of_life.h"

using arr = std::array;
using GOL = GameOfLife;

arr<arr<int, SIZE>, SIZE> ReadInitialState(const std::string& file_name) {
    const int rows, cols;
    arr<arr<int, cols>, rows> initial_state;
    std::ifstream read(file_name);
    if (read) {
        read.ignore(100, '\n');     // ignore first comment
        read >> rows;
        read >> cols;
        int row = 0, col = 0, entry = 0
        while (read >> entry) {
            initial_state[row][col] = entry;
            col += 1;
            if (col == cols) {
                row += 1;
                col = 0;
            }
        }
    }
    else {
        std::cout << "Unable to read file, wrong filename maybe?" << std::endl;
        rows = 0;
        cols = 0;
        initial_state = {{}};
    }
    return initial_state;
}

GOL::GameOfLife(const int rows, const int cols, const std::string& file_name):
        rows_{rows}, cols_{cols} {
        state_ = ReadInitialState(file_name);
    }

void GOL::NextState() {
	arr<arr<int, cols_>, rows_> new_state;
	for (int row = 0; row != rows; row++) {
		for (int col = 0; col != cols; col++) {
			int ctr = 0;
			// count how many neighbors are nonempty
			for (int sub_row = std::max(0, row - 1);
					sub_row != row + 2 && sub_row != rows; sub_row++) {
				for (int sub_col = std::max(0, col - 1);
						sub_col != col + 2 && sub_col != cols; sub_col++) {
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
