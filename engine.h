#ifndef ENGINE_H

#define ENGINE_H

#include <ncurses.h>
#include <math.h>

typedef struct {
	int width;
	int height;
	int** contents;
} VideoMemory;

VideoMemory* createVideoMemory(int width, int heigth);
void freeVideoMemory(VideoMemory* vm);
void initVideoMemory(VideoMemory* memory);
void putPixel(int x, int y, int pixel, VideoMemory* memory);
void refreshScreen(VideoMemory* memory);

#endif
