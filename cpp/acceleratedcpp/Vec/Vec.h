#ifndef __VEC_H
#define __VEC_H

template<class T> class Vec {
public:
    typedef T* iterator;
    typedef T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;

    Vec() { create(); }
    explicit Vec(size_type n, const T& val = T()) { create(n, val); }
    ~Vec() { uncreate(); } // destructor

    Vect(const Vec& v) { create(v.beigin(), v.end()}; // copy constructor

    // size and index
    size_type size() const { return limit - data; }
    T& operator[](size_type i) { return data[i]; }
    const T& operator[](size_type i) { return data[i]; }
    // assignment
    T& operator=(const Vec& v);

    // iterator
    iterator begin() { return data; }
    const_iterator begin() { return data; }
    iterator end() { return limit; }
    const_iterator end() { return limit; }

    // 
    void push_back(const T& val) {
    	if (avail == limit)
    	    grow();
    	unchecked_append(val);
    }
private:
	iterator data; // first element in the Vec
	iterator limit;  // one past the last element
	iterator avail; // pointer to (one past) the last constructed element
};

template<class T> Vec<T>& Vec<T>::operator=(const Vec& rhs) {
	// check for self-assignment
	if (&rhs != this) {
		// free the array in the left-hand side
		uncreate();

		// copy element from the right hand side
		create(rhs.begin(), rhs.end());
	}
	return *this;
}
#endif