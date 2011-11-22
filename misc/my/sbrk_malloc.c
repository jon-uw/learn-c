/**
 * storage allocator from 'TCPL' section 8.7
 * using the system call sbrk
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define NALLOC 1024
typedef long Align;

union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;
    Align x; // force alignment of the block
};

typedef union header Header;

static Header base;
static Header *freep = NULL; // start of the free list

void *my_malloc(unsigned nbytes) {
    Header *p, *prevp;
    Header *morecore(unsigned);
    unsigned nunits;
    
    // round for n blocks
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1; 
    printf("header size: %d, nunits: %d\n", (int)sizeof(Header), nunits);
    if ((prevp = freep) == NULL) { // first use
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {
            if (p->s.size == nunits) {
                prevp->s.ptr = p->s.ptr;
            } else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
        
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep) {
            if ((p = morecore(nunits)) == NULL) {
                return NULL; // can't allocate
            }
        }
    }
}

void my_free(void *ap) {
    printf("in free...\n");
    Header *bp, *p;
    
    bp = (Header *)ap - 1;
    // find the proper location to free ap
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;
    
    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.size;
        bp->s.ptr = p->s.ptr;
    } else {
        bp->s.ptr = p->s.ptr;
    }
    
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else {
        p->s.ptr = bp;
    }
    freep = p;
}

Header *morecore(unsigned nunits) {
    char *cp;
    Header *up;
    
    if (nunits < NALLOC)
        nunits = NALLOC;
    cp = sbrk(nunits * sizeof(Header));
    if (cp == (char *)-1) // no space left
        return NULL;
    up = (Header *)cp;
    up->s.size = nunits;
    my_free((void *)(up + 1));
    return freep;
}

int main() {
    char *test = (char *)my_malloc(15);
    my_free(test);
    return 0;
}



