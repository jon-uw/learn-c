#include <iostream>

int main() {
	std::cout << "Hello world!" << std::endl;
	bool test = true;
	std::cout << test << "\n" << sizeof(test) << std::endl;
	std::cout << (2 < 3) << std::endl;
	// default return value of main is 0
	// need not to add return explicitly
}