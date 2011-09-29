#include <iostream>

using namespace std;

template <class T> T min2(T t1, T t2) {
    T result = t1 < t2 ? t1 : t2;
    return result;
}

template <class Tp> Tp doubleIt(Tp t) {
    Tp result = t * 2;
    return result;
}

int main() {
    cout << "min(3, 4)" << min2(3, 4) << endl;
    cout << "double(4) => " << doubleIt(4) << endl;
    return 0;
}
