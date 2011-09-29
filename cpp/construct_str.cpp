#include <iostream>
#include <string>

int main() {
    const std::string testa(5, '*');
    std::string abc = "abc" + '|';
    //""std::string another = "* " + "dd" + std::string(5, '\\') + " *";
    std::cout << "char length: " << sizeof(char) << std::endl;
    std::cout << "*" << testa << std::endl;
    std::cout << "bbc \n";
    return 0;
}
