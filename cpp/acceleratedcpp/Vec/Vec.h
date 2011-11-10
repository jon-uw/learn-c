#ifndef __VEC_H
#define __VEC_H

#include <algorithm>
#include <memory>

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
    size_type size() const { return avail - data; }
    T& operator[](size_type i) { return data[i]; }
    const T& operator[](size_type i) { return data[i]; }
    // assignment
    T& operator=(const Vec& v);

    // iterator
    iterator begin() { return data; }
    const_iterator begin() { return data; }
    iterator end() { return avail; }
    const_iterator end() { return avail; }

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

    // facilities for memory allocation
    allocator<T> alloc; // object to handle memory allocation, default 

    // alloate and initialize the underlying array
    void create();
    void create(size_type, const T&);
    void create(const_iterator, const_iterator);

    // destroy the element in the array and free the memory
    void uncreate();

    // support functions fro push_back
    void grow();
    void unchecked_append();
};

template<class T> void Vec<T>::create() {
    data = avail = limit = NULL;
}

template<class T> void Vec<T>::create(size_type n, const T& val) {
    data = alloc.allocate(n);
    limit = avail = data + n;
    std::uninitialized_fill(data, limit, val);
}

template<class T> void Vec<T>::create(const_iterator i, const_iterator j) {
    data = alloc.allocate(j - i);
    limit = avail = std::uninitialized_copy(i, j, data);
}

template<class T> void Vec<T>::uncreate() {
    if (data) {
        iterator it = avail;
        while (it != data)
            alloc.destroy(--it);
        alloc.deallocate(data, limit - data);
    }
    data = limit = avail = NULL;
}

template<class T> void Vec<T>::grow() {
    size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);
    uncreate();

    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template<class T> void Vec<T>::unchecked_append(const T& val) {
    alloc.construct(avail++, val);
}

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