#include <string>
#include <iostream>

int main() {
	std::string str = "hoi";
	str[1] = 'u';
	for (auto ch : str)
		std::cout << ch << std::endl;
}