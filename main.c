#include "engine.h"
#include "engineMath.h"
#include <stdlib.h>
#include <time.h>

#define FRAME_TIME_NS 16666667L

void renderLoop(VideoMemory* memory);

int main(int argc, char **argv) {
	//check if the command line arguments are correct
	if (argc != 3) {
		printf("Usage: ./renderer [terminal_width] [terminal_height]\n");
		return 1;
	}

	int screen_width = atoi(argv[1]);	// transform string input into integers
	int screen_height = atoi(argv[2]);

	if (screen_width < 1 || screen_height < 1) {
		printf("Invalid screen dimensions\n");		// are the given dimensions valid
		return 1;
	}

	// create pointer to video memory struct
	VideoMemory* memory = createVideoMemory(screen_width, screen_height);

	initNCurses();
	clearVideoMemory(memory);

	// render loop initializations
	bool running = true;
	int x = 0;

	while (running) {
		// render loop runs 60fps
		struct timespec start = {0};
		struct timespec end = {0};

		clock_gettime(CLOCK_MONOTONIC, &start);
		
		// start of rendering and logic
		
		if (x % 2 == 0) {
			int row = x / screen_width;
			int col = x % screen_width;
			putPixel(col, row, 2, memory);
		}
		x++;

		// refresh screen to see the changes

		refreshScreen(memory);

		// remaining timing stuff
		
		clock_gettime(CLOCK_MONOTONIC, &end);

		long elapsed = (end.tv_sec - start.tv_sec) * 1e9 + 
				(end.tv_nsec - start.tv_nsec);
		
		long remaining = FRAME_TIME_NS - elapsed;

		if (remaining > 0) {
			struct timespec delay = {
				.tv_sec = remaining / 1000000000,
				.tv_nsec = remaining % 1000000000	
			};
			nanosleep(&delay, NULL);
		}
	}

	// end of program
	// free the memory and close program

	freeVideoMemory(&memory);
	endwin();
	return 0;
}
