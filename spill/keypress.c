#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    WINDOW* w;
    w = initscr();
  
    int c;
    /*
       Enable keypad so the user can press a function key (such as an arrow key) and 
       getch returns a single value representing the function key, i. e. KEY_DOWN
    */
    keypad(w, true); 
    move(2,0);

    while((c=getch()) != 27) { // 27 is the escape key 

        if (c == KEY_DOWN) {
            printw("Arrow key down pressed");
        }
        else if (c == KEY_LEFT) {
            printw("Arrow key left pressed");
        }
        else if (c == KEY_UP) {
            printw("Arrow key up pressed");
        }
        else if (c == KEY_RIGHT) {
            printw("Arrow key right pressed");
        }
        printw("\n");

        refresh();
    }
    endwin();
    return 0;
}
