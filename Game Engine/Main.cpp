#include <SDL.h>
#include "stdio.h"
#include "Windows.h"
#include "GameObjectFactory.h"
#include "GameManagers.h"

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

#pragma comment(lib, "legacy_stdio_definitions.lib")

// Global Variable
GLint gProgramID;
GameManagers *gameManagers;

void ConsoleAlloc() {
	// Allocate console for output
	if (AllocConsole())
	{
		FILE* file;

		freopen_s(&file, "CONOUT$", "wt", stdout);
		freopen_s(&file, "CONOUT$", "wt", stderr);
		freopen_s(&file, "CONOUT$", "wt", stdin);

		SetConsoleTitle(L"SDL 2.0 Test");
	}
}

int main(int argc, char* args[])
{
	// Initialize variables
	SDL_Window *pWindow;
	int error = 0;
	bool appIsRunning = true;
	SDL_GLContext openGL_Context;

	ConsoleAlloc();

	// OpenGL 2.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	// Initialize SDL
	if((error = SDL_Init( SDL_INIT_VIDEO )) < 0 )
	{
		printf("Couldn't initialize SDL, error %i\n", error);
		return 1;
	}
	
	pWindow = SDL_CreateWindow("SDL2 window",		// window title
		SDL_WINDOWPOS_UNDEFINED,					// initial x position
		SDL_WINDOWPOS_UNDEFINED,					// initial y position
		800,										// width, in pixels
		800,										// height, in pixels
		SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);

	// Check that the window was successfully made
	if (NULL == pWindow)
	{
		// In the event that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	// Initialize Managers
	gameManagers = new GameManagers();

	// Initialize Rendering Manager
	gameManagers->mpRenderManager->mpWindow = pWindow;
	gameManagers->mpRenderManager->InitGL();
	//gameManagers->mpRenderManager->LoadTexture();
	//gameManagers->mpRenderManager->LoadTexture();

	GameObjectFactory::LoadLevel("Level1.txt");

	// Game loop
	while(true == appIsRunning)
	{
		SDL_Event e;

		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				appIsRunning = false;
			}
		} 
		
		// Start FrameRate Controller
		gameManagers->mpFrameRateController->FrameStart();
		// Clear the buffer
		//SDL_FillRect(gameManagers->pwindowSurface, NULL, 0);

		// Update inputManager
		gameManagers->mpInputManager->Update();

		//Integrate Here
		//gameManagers->mpGameObjectManager->Integrate(gameManagers->mpFrameRateController->GetFrameTime()/1000.0f);
		gameManagers->mpPhysicsManager->Update();
		
		gameManagers->mpEventManager->Update();

		gameManagers->mpGameObjectManager->Update();

		gameManagers->mpRenderManager->Render();
		//gameManagers->mpRenderManager->DrawSprite();

		// Update screen
		SDL_GL_SwapWindow(pWindow);
		printf("FrameTime is %d\n",gameManagers->mpFrameRateController->GetFrameTime());
		gameManagers->mpFrameRateController->FrameEnd();

	}

	delete gameManagers;
	// Close and destroy the window
	SDL_DestroyWindow(pWindow);

	// Quit SDL subsystems
	SDL_Quit();
	
	return 0;
}