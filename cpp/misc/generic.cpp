#include <iostream>
#include <string>

using namespace std;

template<class T> T add(T t1, T t2) {
	return t1 + t2;
}

template<class T> T max2(T a, T b) {
	return a > b ? a : b;
}

int main() {
	string a("abc");
	string b(" testadd");
	cout << add(2, 3) << endl;
	cout << add(a, b) << endl;
	cout << max2(4.2, 5.5) << endl;
	return 0;
}