#include <stdio.h>
// #include <string.h>

#ifdef _WIN32
#include "raylib-6.0_win64_mingw-w64/include/raylib.h"
#else
#include "raylib-6.0_linux_amd64/4include/raylib.h"
#endif


#define WIN_SIZE 800
#define GRID_SIZE 10
#define CELL_PXSIZE 30
#define LIVE_COLOR GRAY

#define STARTPT (WIN_SIZE/2) - (CELL_PXSIZE*GRID_SIZE)/2





int main() {
    InitWindow(WIN_SIZE,WIN_SIZE, "hello, world");
    SetWindowState(FLAG_VSYNC_HINT); // limite 60 fps
    char s[] = "Congrats! You created your first window!";
    int size = MeasureText(s, GetFontDefault().baseSize);

    // return 0;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(10, 10);

        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                DrawRectangleLines(STARTPT + i*CELL_PXSIZE, STARTPT + j*CELL_PXSIZE, CELL_PXSIZE, CELL_PXSIZE, WHITE);
                if (i%2) DrawRectangle(STARTPT + i*CELL_PXSIZE, STARTPT + j*CELL_PXSIZE, CELL_PXSIZE, CELL_PXSIZE, WHITE);
            }
        }

        // DrawGrid(10,10);
        EndDrawing();
    }
    return 0;
}
