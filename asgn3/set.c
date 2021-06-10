#include "set.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Set set_empty(void) {
    return 0;
}

bool set_member(Set s, int x) {
    int mask = 1 << x;
    return ((s & mask) >> x);
}

Set set_insert(Set s, int x) {
    int mask = 1 << x;
    return (s | mask);
}

Set set_remove(Set s, int x) {
    int mask = ~(1 << x);
    return (s & mask);
}

Set set_union(Set s, Set t) {
    return (s | t);
}

Set set_intersect(Set s, Set t) {
    return (s & t);
}

Set set_difference(Set s, Set t) {
    return (s & ~t);
}

Set set_complement(Set s) {
    return ~s;
}

//int main(void){
//Set a = 1<<31;
//printf("%d\n", set_member(a,31));// a = passed #, int = check pos.
//return 0;
//}
