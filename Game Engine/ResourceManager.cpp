#include "ResourceManager.h"
#include "stdio.h"
#include "SDL_surface.h"
#include "stb_image.h"


ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
	for (auto &it : mSurfaces)
		SDL_FreeSurface(it.second);
}

SDL_Surface* ResourceManager::LoadSurface(char * pFilePath)
{
	SDL_Surface *pSurface = mSurfaces[pFilePath];
	if (pSurface)
		return pSurface;

	pSurface = SDL_LoadBMP(pFilePath);
	if (pSurface)
		mSurfaces[pFilePath] = pSurface;

	return pSurface;
}

/*
GLuint ResourceManager::LoadTexture(char * pFilePath)
{
	GLuint textureID;
	int width, height, n;

	std::string fullPath = "..\\Resources\\";
	fullPath += "myImage.bmp";

	//mpSurface = gameManagers->mpResourceManager->LoadSurface((char*)fullPath.c_str());

	unsigned char *data = stbi_load("Mario.png", &width, &height, &n, 0);

	glGenTextures(1, &textureID);

	// Bind created texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	// Load the data
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, data.Width, data.Height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, &data);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
	return textureID;
}
*/

GLuint ResourceManager::LoadTexture(char * pFilePath)
{

	int width, height, n;
	GLuint textureID = mTextures[pFilePath];

	if (textureID) return textureID;
	/*
	std::string fullPath = "..\\Resources\\";
	fullPath += "myImage.bmp";

	//mpSurface = gameManagers->mpResourceManager->LoadSurface((char*)fullPath.c_str());
	*/
	//std::string fullPath = "..\\Resources\\";
	//pFilePath = "Mario.png";

	//fullPath += pFilePath;
	unsigned char *data = stbi_load(pFilePath, &width, &height, &n, 0);
	
	glGenTextures(1, &textureID);

	// Bind created texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Load the data
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, data.Width, data.Height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, &data);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
	mTextures[pFilePath] = textureID;

	return textureID;
}
