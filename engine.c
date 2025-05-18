#include "engine.h"

VideoMemory* createVideoMemory(int width, int height) {
	VideoMemory* vm = malloc(sizeof(VideoMemory));			// allocate memory for struct
	if (!vm) return NULL;
	vm->width = width;			// assing variables
	vm->height = height;

	vm->contents = malloc(height * sizeof(int*));		// allocate memory for y dimension of two dimensional array
	if (!vm->contents) {
		free(vm);
		return NULL;
	}

	for (int i = 0; i < height; i++) {			// allocate memory for x dimension of two dimensional array
		vm->contents[i] = malloc(width * sizeof(int));
		if (!vm->contents[i]) {
			for (int j = 0; j < i; j++) {
				free(vm->contents[j]);
			}
			free(vm->contents);
			free(vm);
			return NULL;
		}
	}
	return vm;
}

void freeVideoMemory(VideoMemory** vmPtr) {
	if (!vmPtr || !*vmPtr) return;
	VideoMemory* vm = *vmPtr;
	for (int i = 0; i < vm->height; i++) {		// free x dimension of two dimensional array
		free(vm->contents[i]);
	}
	free(vm->contents);		// free y dimension of two dimensional array
	free(vm);		// free the rest of the struct
	*vmPtr = NULL;
}

void clearVideoMemory(VideoMemory* memory) {
	for (int y = 0; y < memory->height ; y++) {		// loop through all rows in video memory
		for (int x = 0; x < memory->width; x++) {	// loop through all elements in row in video memory
			memory->contents[y][x] = 0;	// clear element to blank space
		}
	}
}

void putPixel(int x, int y, int pixel, VideoMemory* memory) {
	if (abs(x) > (memory->width / 2)) {
		return;
	}
	if (abs(y) > (memory->height / 2)) {
		return;
	}
	int Sx = (memory->width / 2) + x;		// transform coordinate system from (0,0) being in the top left corner to being in the center
	int Sy = (memory->height / 2) - y;
	memory->contents[Sy][Sx] = pixel;
}

void refreshScreen(VideoMemory* memory) {
	for (int y = 0; y < memory->height; y++) {		// loop through all the pixels in video memory and write then onto the terminal screen
		for (int x = 0; x < memory->width; x++) {
			move(y, x);
			switch (memory->contents[y][x]) {
				case 0:
					addch(' ');
					break;
				case 1:
					addch('.');
					break;
				case 2:
					addch(':');
					break;
				case 3:
					addch('#');
					break;
			}
		}
	}
	refresh(); 	// refresh ncurses terminal screen to see the pixels
}

void initNCurses() {
	initscr();
	noecho();
	curs_set(0);
	nodelay(stdscr, TRUE);
}
