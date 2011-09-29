#include <iostream>
extern "C" {
#include "test_c.h"
}

using namespace std;

//extern "C" int add(int a, int b);

int main() {
    cout << "value got from c: " << add(2, 5) << endl;
    return 0;
}
