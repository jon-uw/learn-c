#include "median.h"

using std::domain_error;
using std::sort;
using std::vector;

double median(vector<double> vec) {
	typedef vector<double>::size_type vec_sz;
	vec_sz size = vec.size();
	if (size == 0) {
		throw domain_error("vector can not be empty!");
	}
	sort(vec.begin(), vec.end());
	vec_sz mid = size / 2;
	return size % 2 == 0 ? (vec[mid - 1] + vec[mid]) / 2
	                     : vec[mid];
}