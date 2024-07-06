#include <SDL3/SDL_error.h>
#include <trielo/trielo.hpp>

#include <SDL3/SDL_custom.h>

void SDL_PrintError() {
	Trielo::trielo<SDL_GetError>(Trielo::Success<const char*>(nullptr));
};