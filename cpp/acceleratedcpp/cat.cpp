#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
	int error_count = 0;
	for (int i = 1; i < argc; i++) {
		ifstream in(argv[i]);
		string s;
		if (in) {
		    while (getline(in, s))
		        cout << s << endl;
		    cout << endl << "-----------------------------------" <<endl;
		} else {
			cerr << "can't open file: " << argv[i] << endl;
			error_count++;
		}
	}

	return error_count;
}
