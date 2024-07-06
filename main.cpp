#include <iostream>

#include <trielo/trielo.hpp>
#include <SDL3/SDL.h>
#include <SDL3/SDL_custom.h>

int main() {
	Trielo::trieloxit_lambda<SDL_Init>(
		Trielo::Success(0),
		SDL_PrintError,
		SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER
	);

	SDL_Window* window {
		Trielo::trielo_lambda<SDL_CreateWindow>(
			Trielo::Error<SDL_Window*>(nullptr),
			SDL_PrintError,
			PROJECT_NAME,
			1280,
			720,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
		)
	};

	if(window == nullptr) {
		Trielo::trielo<SDL_Quit>();
		return EXIT_FAILURE;
	}

    SDL_GLContext gl_context {
		Trielo::trielo_lambda<SDL_GL_CreateContext>(
			Trielo::Error<SDL_GLContext>(nullptr),
			SDL_PrintError,
			window
		)
	};

	if(gl_context == nullptr) {
		Trielo::trielo<SDL_Quit>();
		return EXIT_FAILURE;
	}

    Trielo::trielo_lambda<SDL_GL_MakeCurrent>(Trielo::Success(0), SDL_PrintError, window, gl_context);
    Trielo::trielo_lambda<SDL_GL_SetSwapInterval>(Trielo::Success(0), SDL_PrintError, 1); // Enable vsync
    Trielo::trielo_lambda<SDL_ShowWindow>(Trielo::Success(0), SDL_PrintError, window);

	bool done { false };
	while(done == false) {
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			if(
				event.type == SDL_EVENT_QUIT
				|| (
					event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED
					&& event.window.windowID == SDL_GetWindowID(window)
				)
			) {
				done = true;
			}
		}
        if(SDL_GL_SwapWindow(window) != 0) {
			std::cout << "ERROR: SDL_GL_SwapWindow(window) != 0\n";
		}
	}

    Trielo::trielo_lambda<SDL_GL_DeleteContext>(Trielo::Success(0), SDL_PrintError, gl_context);
	Trielo::trielo<SDL_DestroyWindow>(window);
	Trielo::trielo<SDL_Quit>();
	return EXIT_SUCCESS;
}