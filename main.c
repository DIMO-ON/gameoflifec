#include <stdio.h>
#include <malloc.h>
#include <string.h>

#ifdef _WIN32
#include "raylib-6.0_win64_mingw-w64/include/raylib.h"
#else
#include "raylib-6.0_linux_amd64/include/raylib.h"
#endif


#define WIN_SIZE 800
#define GRID_SIZE 10
#define GRID_AREA GRID_SIZE*GRID_SIZE 
#define CELL_PXSIZE 30
#define LIVE_COLOR GRAY

#define STARTPT (WIN_SIZE/2) - (CELL_PXSIZE*GRID_SIZE)/2


void map_state_pixel(int x, int y, int state) {
	if (state)
		DrawRectangle(STARTPT + x*CELL_PXSIZE, STARTPT + y*CELL_PXSIZE, CELL_PXSIZE, CELL_PXSIZE, WHITE);
	else
		DrawRectangleLines(STARTPT + x*CELL_PXSIZE, STARTPT + y*CELL_PXSIZE, CELL_PXSIZE, CELL_PXSIZE, GRAY);
}

// int getidx(int x, int y, int xofst, int yofst) {
int getidx(int x, int y, int xofst, int yofst, int cell) {
	int newx = (x + xofst);
	int newy = (y + yofst);

	int newidx = newy*GRID_SIZE + newx;
	int actualidx = y*GRID_SIZE + x;
	if (cell == 1) printf("[%d]   :: actualpos: (%d, %d), newpos: (%d, %d)\n", cell, x, y, newx, newy);
	if (newy >= 0 && newy < GRID_SIZE &&
		newx >= 0 && newx < GRID_SIZE)
		return newidx;

	return -1;
}


int update_cellstate(int x, int y, int* stategrid, int* newstategrid) {
	int actualidx = y*GRID_SIZE + x;
	int count = 0;
	int neighbors[][2] = {
		{ 1, 0}, // est
		{ 1, 1}, // sud-est
		{ 0, 1}, // sud
		{-1, 1}, // sud-ovest
		{-1, 0}, // ovest
		{-1,-1}, // nord-ovest
		{ 0,-1}, // nord
		{-1, 1}  // nord-est
	};

	for (int i = 0; i < 8; i++) {
		// int idx = getidx(x, y, neighbors[i][0], neighbors[i][1]);
		int idx = getidx(x, y, neighbors[i][0], neighbors[i][1], stategrid[actualidx]);
		if (idx >= 0 && idx < GRID_SIZE * GRID_SIZE)
			count += stategrid[idx];
	}

	if (stategrid[actualidx] == 1) {
		if (count < 2 || count > 3) newstategrid[actualidx] = 0;
		else newstategrid[actualidx] = 1;
	} else {
		if (count == 3) newstategrid[actualidx] = 1;
		else newstategrid[actualidx] = 0;
	}
}

int checkcells(int *grid) {
	for (int i = 0; i < GRID_AREA; i++)
		if (grid[i]) return 1;

	return 0;
}


int main() {
	int *stategrid = calloc(sizeof(int), GRID_SIZE*GRID_SIZE);
	int *newstategrid = calloc(sizeof(int), GRID_SIZE*GRID_SIZE);
	// initiate state grid
	stategrid[0*GRID_SIZE] = 1;
	stategrid[1*GRID_SIZE] = 1;
	stategrid[2*GRID_SIZE] = 1;
	
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
				map_state_pixel(j, i, stategrid[i*GRID_SIZE + j]); 
            }
        }

        EndDrawing();
		if (checkcells(stategrid)) {
			WaitTime(3);

			for (int i = 0; i < GRID_SIZE; i++) {
				for (int j = 0; j < GRID_SIZE; j++) {
					update_cellstate(j, i, stategrid, newstategrid); 
				}
			}
			memcpy(stategrid, newstategrid, GRID_SIZE * GRID_SIZE * sizeof(int));
		}

    }
    return 0;
}
