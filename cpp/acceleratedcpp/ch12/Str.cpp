#include <cctype>
#include "Str.h"

using namespace std;

istream& operator>>(istream& is, Str& s) {
	s.data.clear();
	char c;
	while (is.get(c) && isspace(c)); // nothing to do
	// if there is still something to read
	if (is) {
		do s.data.push_back(c);
		while (is.get(c) && !isspace(c));

		// if we read space, then put it back on the istream
		if (is)
		    is.unget();
	}
	return is;
}

ostream& operator<<(ostream& os, const Str& s) {
	for (Str::size_type i = 0; i != s.size(); i++) {
		cout << "now fetch i: " ;
		os << s[i];
		os << endl;
	}
	return os;
}

Str operator+(const Str& s1, const Str& s2) {
	Str s = s1;
	s += s2;
	return s;
}