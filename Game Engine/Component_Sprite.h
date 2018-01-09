#pragma once
#include <SDL.h>
#include "GameObject.h"
#include "Component.h"
#include "GLEW\include\GL\glew.h"
#include <SDL_opengl.h>

class Component_Sprite : public Component
{
public:
	Component_Sprite();
	~Component_Sprite();
	void Update();
	void Render();
	void SerializeOld(FILE **fpp);
	void Serialize(FILE **fpp);

	SDL_Surface *mpSurface;
	SDL_Rect	mImageRect;
	SDL_Surface *mpWindowSurface;
	int mImagePosX;
	GLuint mTextureID;
	float angle = 0.0f;
};

