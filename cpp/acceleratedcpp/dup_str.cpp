#include <iostream>
#include <string>

using namespace std;

char* dup_str(const char *str) {
	size_t length = strlen(str) + 1;
	char* result = new char[length];
    copy(str, str + length, result);
    return result;
}

int main() {
	const char* str = "test it";
	char* ret = dup_str(str);
	cout << "get string: " << ret << endl;
	delete [] ret;
	return 0;
}
