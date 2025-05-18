#ifndef ENGINE_H

#define ENGINE_H

#include <ncurses.h>
#include "engineMath.h"

typedef struct {
	int width;
	int height;
	int** contents;
} VideoMemory;

VideoMemory* createVideoMemory(int width, int heigth);
void freeVideoMemory(VideoMemory** vm);
void clearVideoMemory(VideoMemory* memory);
void putPixel(int x, int y, int pixel, VideoMemory* memory);
void refreshScreen(VideoMemory* memory);
void initNCurses();
Vector3 canvasToViewport(float x, float y, float Vwidth, float Vheight, int Cwidth, int Cheight);
int traceRay(Vector3 cameraPos, Vector3 dir, float t_min, float t_max);

#endif
