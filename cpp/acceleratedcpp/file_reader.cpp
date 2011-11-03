#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	string filename("file_reader.cpp");
	ifstream in(filename.c_str());
	string s;
	while (getline(in, s))
	    cout << s << endl;
	
	return 0;
}
