#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

#define KEY_UP 87
#define KEY_DOWN 83
#define KEY_LEFT 65
#define KEY_RIGHT 68

bool key_is_pressed(int key) {
    return (bool)(GetKeyState(key) & 0x8000);
}

int main() {
    printf("hey\n");
    while (!key_is_pressed(VK_ESCAPE)) {
        if (key_is_pressed(KEY_UP)) {
            printf("w \n");
        } else if (key_is_pressed(KEY_DOWN)) {
            printf("s \n");
        } else if (key_is_pressed(KEY_LEFT)) {
            printf("a \n");
        } else if (key_is_pressed(KEY_RIGHT)) {
            printf("d \n");
        }
    }
    return 0;
}