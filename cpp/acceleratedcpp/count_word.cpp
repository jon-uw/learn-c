#include <iostream>
#include <map>

using namespace std;

int main() {
	string s;
	map<string, int> counters;

	while (cin >> s)
	    ++counters[s];

	// write the result
	for (map<string, int>::const_iterator it = counters.begin(); it != counters.end(); it++)
	    cout << it->first << "\t" << it->second << endl;

	return 0;
}