#include <stdexcept>
#include <vector>
#include "grade.h"
#include "median.h"
#include "student_info.h"

using namespace std;

double grade(double midterm, double final, double homework) {
	return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double grade(double midterm, double final, const vector<double>& hw) {
	return grade(midterm, final, median(hw));
}

double grade(const Student_info& s) {
	return grade(s.midterm, s.final, s.homework);
}

bool fgrade(const Student_info& s) {
	return grade(s) < 60;
}