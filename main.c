#include <stdio.h>
// #include <string.h>
#include "raylib-6.0_linux_amd64/include/raylib.h"

int main() {
    InitWindow(800,800, "hello, world");
    char s[] = "Congrats! You created your first window!";
    int size = MeasureText(s, GetFontDefault().baseSize); 
    
    // return 0;
    while (!WindowShouldClose()) {
        BeginDrawing();
        // ClearBackground(BLACK);
        // DrawText(s, 800/2 - size/2 * 2, 800/2, 20, WHITE);

        for (int i = 0; i < 4; i++) {
                // RLAPI void DrawRectangle(int posX, int posY, int width, int height, Color color);                        // Draw a color-filled rectangle
                // RLAPI void DrawRectangleLines(int posX, int posY, int width, int height, Color color);                   // Draw rectangle outline
                DrawRectangleLines(800/2-100, 800/2 + i*20, 100, 20, WHITE);
        }

        // DrawGrid(10,10);
        EndDrawing();
    }
    return 0;
}
