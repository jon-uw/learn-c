#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void) {
    int on_stack, *on_heap;

    // local variables are stored on the stack
    on_stack = 42;
    printf("stack address: %p\n", &on_stack);

    // malloc allocates on heap memory
    on_heap = (int*)malloc(sizeof(int));
    printf("heap address: %p\n", on_heap);    

    printf("run `pmap %d`\n", getpid());
    pause();
}
