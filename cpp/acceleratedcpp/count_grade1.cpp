#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>


using std::cin;
using std::cout;
using std::endl;
using std::setprecision;
using std::string;
using std::streamsize;
using std::sort;
using std::vector;

int main() {
	// ask the student' name
	cout << "Please enter your first name: ";
	string name;
	cin >> name;
	cout << "Hello, " << name << "!" << endl;

	// ask for grades
	cout << "Please enter your midterm and final exam grades: ";
	double midterm, final;
	cin >> midterm >> final;

	// ask for the homework grades
	cout << "Enter all your home work grades, "
	     << "followed by end-of-file: ";

    // count the median of homeworks
    vector<double> homework;
    double x;
    while (cin >> x)
        homework.push_back(x);
    
    typedef vector<double>::size_type vec_sz;
    vec_sz size = homework.size();
    if (size == 0) {
    	cout << "You must enter your grade. "
    	        "Please try it again." << endl;
    	return 1;
    }

    // sort the grades
    sort(homework.begin(), homework.end());
    // compute the median homework grade
    vec_sz mid = size / 2;
    double median;
    median = size % 2 == 0 ? (homework[mid - 1] + homework[mid]) / 2
                           : homework[mid];

    streamsize prec = cout.precision();
    cout << "Your final grade is: " << setprecision(3)
         << 0.2 * midterm + 0.4 * final + 0.4 * median
         << setprecision(prec) << endl;
    
    return 0;
}