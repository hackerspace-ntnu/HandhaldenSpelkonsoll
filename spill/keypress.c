#ifdef _WIN64
#include <conio.h>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#else
#include <curses.h>
#endif

#include <stdio.h>
#include <stdlib.h>


int keyPressedUnix(void) { // for Linux and Mac
    int c;

    initscr();
    //  Enable keypad so that getch returns a single value representing an arrow key
    keypad(stdscr, true); 

    while((c=getch()) != 27) { // 27 is the escape key 

       if (c == KEY_UP || c == KEY_DOWN || c == KEY_LEFT || c == KEY_RIGHT) {
           return c;
       } else {
           endwin();
       }
    }
}

int keyPressedWindows(void) { // for Windows
    char c;

    while ((c=getch()) != 27) {
        if (c == 0) {
            switch(getch()) {
                case KEY_UP:
                case KEY_DOWN:
                case KEY_LEFT:
                case KEY_RIGHT:
                    return c;
                    break;
            }
        }
    }
}

int main() {
    #ifdef _WIN64
    char c;
    c = keyPressedWindows();
    #else
    int c;
    c = keyPressedUnix();
    if (c == KEY_UP || c == KEY_DOWN || c == KEY_LEFT || c == KEY_RIGHT) {
           printf("Arrow key pressed");
    }
    #endif
    return 0;
}
