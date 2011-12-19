#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <stddef.h>
#include <string.h>

struct passwd * getpwname(const char *name) {
    struct passwd *ptr;
    setpwent();
    while ((ptr = getpwent()) != NULL) {
        if (strcmp(name, ptr->pw_name) == 0)
	    break;
    }
    endpwent();

    return ptr;
}

int main() {
    printf("uid of gosudream is: %d\n ", getpwname("gosudream")->pw_uid);

    exit(0);
}
