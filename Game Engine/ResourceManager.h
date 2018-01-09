#pragma once
#include <string>
#include <unordered_map>
#include "GLEW\include\GL\glew.h"
#include <SDL_opengl.h>

class SDL_Surface;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	SDL_Surface* LoadSurface(char *pFilePath);
	GLuint LoadTexture(char * pFilePath);
	//GLuint LoadTextureOld(char * pFilePath);

private:
	std::unordered_map<std::string, SDL_Surface*>mSurfaces;
	std::unordered_map<std::string, GLuint>mTextures;
};

