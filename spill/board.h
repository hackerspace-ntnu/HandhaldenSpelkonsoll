#include <stdio.h>
#include <stdlib.h>
struct Body {
    short int x;
    short int y;
    char isHead; // (1=true, 0=false)
    struct Body* next; // Pointer to next part of Body
    struct Body* prev; // Pointer to previous part of Body
};