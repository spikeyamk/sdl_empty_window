#include <iostream>

#include <SDL3/SDL_error.h>

void SDL_PrintError() {
	std::cout << SDL_GetError() << std::endl;
}
