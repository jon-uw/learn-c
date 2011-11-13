#ifndef __STR_H
#define __STR_H

#include <iostream>
#include <vector>

//using namespace std;

class Str {
	friend std::istream& operator>>(std::istream&, Str&);
	//friend std::ostream& operator<<(std::ostream&, const Str&);
public:
    Str& operator+=(const Str& s) {
        std::copy(s.data.begin(), s.data.end(), std::back_inserter(data));
        return *this;
    }
    typedef std::vector<char>::size_type size_type;	
    // default constructor
    Str() {}
    Str(size_type n, char c): data(n, c) {}
    Str(const char* cp) {
    	std::cout << "in one argument constructor..." << std::endl;
    	std::copy(cp, cp + std::strlen(cp), std::back_inserter(data));
    }

    // create a str from the range denoted by the iterators b and e
    template<class In> Str(In b, In e) {
    	std::copy(b, e, std::back_inserter(data));
    }

    // operator overload
    char& operator[](size_type i) { 
    	std::cout << "fetch " << i << "of the char" << std::endl;
	    return data[i]; }
    const char& operator[](size_type i) const { return data[i]; }

    // other member function
    size_type size() const { return data.size(); }
    // for test
    const std::vector<char>& getData() const { return data; }

private:
    std::vector<char> data;
};

// input and out put method
//std::istream& operator>>(std::istream&, Str&);
std::ostream& operator<<(std::ostream&, const Str&);
Str operator+(const Str&, const Str&);
#endif