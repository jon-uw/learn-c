#include <stdio.h>

struct align1 {
  int a;
  char b;
  short c;
};

struct align2 {
  char a;
  int  b;
  short c;
};

int main(void) {
    printf("size a1=%d a2=%d\n", sizeof(struct align1),
        sizeof(struct align2));
    return 0;
}


