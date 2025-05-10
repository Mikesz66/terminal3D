#include "engine.h"
#include <stdlib.h>

int main(int argc, char **argv) {
	// check if the command line arguments are correct
	if (argc != 3) {
		printf("Usage: ./engine (terminal width) (terminal height)\n");
		return 1;
	}

	int screen_width = atoi(argv[1]);	// change input from string to int
	int screen_height = atoi(argv[2]);

	if (screen_width < 1 || screen_height < 1) { 		// check if the screen dimensions are not 0 and not negative
		printf("Invalid screen dimensions\n");
		return 1;
	}

	// create pointer to video memory struct
	VideoMemory* memory = createVideoMemory(screen_width, screen_height); 
	

	// basic initialization
	initscr();		// init ncurses screen	
	noecho();		// don't show pressed keys
	curs_set(0);		// hide cursor
	initVideoMemory(memory);	// init video memory to blank spaces
	
	// engine loop
	putPixel(0, 0, 1, memory);
	refreshScreen(memory);
	
	// end of program
	refresh();		// show what's on the screen
	getch();		// wait for user input to close application
	
	freeVideoMemory(memory);
	endwin();		// close ncurses session
	return 0;
}

VideoMemory* createVideoMemory(int width, int height) {
	VideoMemory* vm = malloc(sizeof(VideoMemory));			// allocate memory for struct
	vm->width = width;			// assing variables
	vm->height = height;

	vm->contents = malloc(height * sizeof(int*));		// allocate memory for y dimension of two dimensional array
	for (int i = 0; i < height; i++) {			// allocate memory for x dimension of two dimensional array
		vm->contents[i] = malloc(width * sizeof(int));
	}
	return vm;
}

void freeVideoMemory(VideoMemory* vm) {
	for (int i = 0; i < vm->height; i++) {		// free x dimension of two dimensional array
		free(vm->contents[i]);
	}
	free(vm->contents);		// free y dimension of two dimensional array
	free(vm);		// free the rest of the struct
}

void initVideoMemory(VideoMemory* memory) {
	for (int y = 0; y < memory->height ; y++) {		// loop through all rows in video memory
		for (int x = 0; x < memory->width; x++) {	// loop through all elements in row in video memory
			memory->contents[y][x] = 0;	// initialize element to blank space
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
					addch('#');
					break;
			}
		}
	}
	refresh(); 	// refresh ncurses terminal screen to see the pixels
}
