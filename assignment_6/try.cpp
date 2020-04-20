#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <cmath>

using std::cout;	using std::endl;


std::string convertCharToBitstring(unsigned char nr) {
	int value = (int)nr;
	std::string byte = "";
	for (int i = 7; i != -1; i--) {
		if (value - (int)pow(2, i) >= 0) {
			byte += '1';
			value -= (int)pow(2, i);
		}
		else
			byte += '0';
	}
	return byte;
}

unsigned char convertBitstringToChar(std::string byte) {
	unsigned char c = 0;
	for (int i = 0; i != 8; i++) {
		c <<= 1;
		if (byte[i] == '1') c |= 1;
	}
	return c;
}

int main() {
	

	// if (std::FILE* file = std::fopen("byte.bin", "wb")) {
	// 	if (std::fwrite(&c, sizeof(c), 1, file))
	// 		cout << "wrote to file" << endl;
	// 	std::fclose(file);
	// }
	

	// unsigned char d = 0;
	// if (std::FILE* file1 = std::fopen("byte.bin", "rb")) {
	// 	if (std::fread(&d, sizeof(d), 1, file1))
	// 		cout << "read from file" << endl;
	// 	std::fclose(file1);
	// }
	
	
}