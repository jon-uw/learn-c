#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "grade.h"
#include "student_info.h"

using namespace std;

int main() {
	vector<Student_info> students;
	Student_info record;
	string::size_type maxlen = 0;

	while (read(cin, record)) {
		maxlen = max(maxlen, record.name.size());
		students.push_back(record);
		//cout << "read: " + record.name << endl;
	}

	// sort the student records according to their names
	sort(students.begin(), students.end(), compare);

	// write the names and grades
	//for (vector<Student_info>::size_type i = 0; i < students.size(); i++) {
		// write the name, padded on the right to maxlen + 1
	//	cout << students[i].name << string(maxlen + 1 - students[i].name.size(), ' ');

        // ignore the exception first
    //    try {
    //        double final_grade = grade(students[i]);
    //        streamsize prec = cout.precision();
    //        cout << setprecision(3) << final_grade << setprecision(prec);
    //    } catch (domain_error e) {
    //    	cout << e.what() << endl;
    //    	cout << "error parse the grade of: " << students[i].name;
    //    }
        
    //    cout << endl;		
	//}

		/*using iterator*/	
	for (vector<Student_info>::const_iterator iter = students.begin(); 
	        iter != students.end(); iter++) {
		cout << (*iter).name << string(maxlen + 1 - (*iter).name.size(), ' ');

        // ignore the exception first
        try {
            double final_grade = grade(*iter);
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade << setprecision(prec);
        } catch (domain_error e) {
        	cout << e.what() << endl;
        	cout << "error parse the grade of: " << (*iter).name;
        }
        
        cout << endl;		
	}

	return 0;
}