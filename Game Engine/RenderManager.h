#pragma once
#include <SDL.h>
#include "GameObject.h"
#include "GLEW\include\GL\glew.h"
#include <SDL_opengl.h>
#include <fstream>
#include <iostream>
#include <string>

#include "Affine3D.h"

class RenderManager
{
public:
	RenderManager();
	~RenderManager();

	SDL_GLContext InitGL();
	void LoadShaders(void);
	void LoadTexture();
	void DrawSprite();
	void Render();

	GLint gProgramID;
	SDL_Window *mpWindow;
	GLuint bufferIDs[3];
	GLuint textureID;
	GLuint texCoordBuffer;
};

