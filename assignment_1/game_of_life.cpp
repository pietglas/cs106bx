#include <array>
#include "game_of_life.h"

using arr = std::array;
using GOL = GameOfLife

arr<arr<int, cols_>, rows_> GOL::NextState() {
	for (int row = 0; row != rows; row++) {
		for (int col = 0; col != cols; col++) {
			int ctr = 0;
			// count how many neighbors are nonempty 
			for (int sub_row = std::max(0, row - 1); 
					sub_row != row + 2 && sub_row != rows; sub_row++) {
				for (int sub_col = std::max(0, col - 1);
						sub_col != col + 2 && sub_col != cols; sub_col++) {
					if ((old_array[sub_row][sub_col] != 0) && 
							(sub_col != col || sub_row != row))
						ctr += 1;
				}
			}
			// set new entry according to game rules
			if (ctr == 2) new_array[row][col] = old_array[row][col];
			else if (ctr == 3) new_array[row][col] = old_array[row][col] + 1;
			else new_array[row][col] = 0;
		}
	}
	return new_array;
}