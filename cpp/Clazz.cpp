#include <iostream>
using namespace std;

class Test{
    public:
        Test() {
	    cout<< "initializing test..\n";
	}
	~Test() {
	    cout << "clear test...\n";
	}
};

int main() {
    Test *test  = new Test();
    cout << "int main.\n";
    delete test;
}
