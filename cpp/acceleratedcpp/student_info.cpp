#include "student_info.h"
#include <iostream>

using namespace std;

bool compare(const Student_info& s, const Student_info& s1) {
	return s.name < s1.name;
}

istream& read(istream& in, Student_info& s) {
	// read and store the student's name and grade
	in >> s.name >> s.midterm >> s.final;
    //cout << s.name + " readed..";
	return read_hw(in, s.homework);
}

istream& read_hw(istream& in, vector<double>& hw) {
	if (in) {
		hw.clear();
        
		// read homework grades
		double x;
		while (in >> x)
		    hw.push_back(x);
		
		in.clear();
	}
	return in;
}