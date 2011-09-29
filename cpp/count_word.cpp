#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    string s;
    map<string, int> counters;

    // read the input
    while (cin >> s)
        ++counters[s];

    cout << "\n the result is: \n";
    // write the result out
    for (map<string, int>::const_iterator it = counters.begin();
        it != counters.end(); it++) {
        cout << it->first << "\t" << it->second << endl;	
    }

    return 0;
}
