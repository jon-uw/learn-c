// ask for a person's name, and greet the person

#include <iostream>
#include <string>

int main() {
	// ask for the person's name
	std::cout << "Please enter your first name: ";
	std::string name;
	std::cin >> name;

	// greet the person
	std::cout << "Hello, " << name << "!" << std::endl;
    return 0;
}