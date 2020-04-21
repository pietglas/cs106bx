#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <cmath>
#include <map>

using std::cout;	using std::endl;

std::map<char, int> countChars(const std::string& file_name) {
    std::string text_;
    std::map<char, int> char_occurrences_;
    std::ifstream textfile(file_name);
    if (!textfile) {
        cout << "An error occurred, maybe the pathfile is wrong?" << endl;
    }
    else {
        char character = '\0';
        while (textfile.get(character)) {
            if (!char_occurrences_.try_emplace(character, 1).second)
                ++char_occurrences_[character];
            text_ += character;     // save text as a string
        }
    }
    cout << text_ << endl;
    return char_occurrences_;
}

int main() {
	
	std::map<char, int> chars = countChars("sometext.txt");
	for (auto& letter: chars) 
		cout << letter.first << ", " << letter.second << endl;


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