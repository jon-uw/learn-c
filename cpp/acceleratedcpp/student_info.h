#ifndef __STUDENT_INFO_H
#define __STUDENT_INFO_H

#include <iostream>
#include <string>
#include <vector>

struct Student_info {
    std::string name;
    double midterm, final;
    std::vector<double> homework;	
};

bool compare(const Student_info& s, const Student_info& s1);
std::istream& read(std::istream& in, Student_info& student);
std::istream& read_hw(std::istream& in, std::vector<double>& hw);

#endif