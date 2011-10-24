#ifndef __GRADE_H
#define __GRADE_H

#include <vector>
#include "student_info.h"

double grade(double midterm, double final, double homework);
double grade(double midterm, double final, const std::vector<double>& hw);
double grade(const Student_info& s);
#endif