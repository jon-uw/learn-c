#include <iostream>
#include "Str.h"

using namespace std;

int main() {
	Str s = "abc";
	cout << s << endl;
	cout << "enter a str please: ";
	cin >> s;
	cout << "s is now: " << s << endl;
	cout << "s.length = " << s.getData().size() << endl;
	cout << s[5] << endl;

	return 0;
}