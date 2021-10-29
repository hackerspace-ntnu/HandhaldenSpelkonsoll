#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int main() {
    char c;

    while ((c=getch()) != 27) {
        if (c == 0) {
            switch(getch()) {
                case KEY_UP:
                    printf("w \n");
                    break;
                case KEY_DOWN:
                    printf("s \n");
                    break;
                case KEY_LEFT:
                    printf("a \n");
                    break;
                case KEY_RIGHT:
                    printf("d \n");
                    break;
            }
        }
    }
    return 0;
}