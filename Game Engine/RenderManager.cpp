#include "RenderManager.h"
#include "GameManagers.h"
#include "Component_Sprite.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

using namespace std;
extern GameManagers *gameManagers;

RenderManager::RenderManager()
{
	//InitGL();
}

RenderManager::~RenderManager()
{
}

string LoadTextFile(const char * fname)
{
	string out,
		line;
	ifstream in(fname);
	getline(in, line);
	while (in) {
		out += line + "\n";
		getline(in, line);
	}
	return out;
}

void RenderManager::LoadShaders(void)
{
	gProgramID = glCreateProgram();

	// Compile Vertex Shader

	string verttextstr = LoadTextFile("shader.vert").c_str();
	const char *verttext = verttextstr.c_str();

	GLuint vShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShaderID, 1, &verttext, 0);

	glCompileShader(vShaderID);
	GLint status;
	glGetShaderiv(vShaderID, GL_COMPILE_STATUS, &status);

	if (!status) {
		cerr << "vertex shader failed to compile" << endl;
		char buffer[1024];
		glGetShaderInfoLog(vShaderID, 1024, 0, buffer);
		cerr << buffer << endl;
	}
	else {
		glAttachShader(gProgramID, vShaderID);
	}


	// Compile Pixel Shader

	std::string fragtextstr = LoadTextFile("shader.frag");
	const char *fragtext = fragtextstr.c_str();

	GLuint fShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShaderID, 1, &fragtext, 0);
	glCompileShader(fShaderID);

	//GLint status;
	glGetShaderiv(fShaderID, GL_COMPILE_STATUS, &status);
	if (!status) {
		std::cerr << "fragment shader failed to compile" << std::endl;
		char buffer[1024];
		glGetShaderInfoLog(fShaderID, 1024, 0, buffer);
		std::cerr << buffer << std::endl;
	}
	else {
		glAttachShader(gProgramID, fShaderID);
	}


	glLinkProgram(gProgramID);

	GLsizei returnedLength = 0;
	const unsigned int logSize = 10000;
	char log[logSize];
	memset(log, 0, logSize * sizeof(char));
	glGetProgramInfoLog(gProgramID, logSize, &returnedLength, log);
	printf("%s\n", log);

	glUseProgram(gProgramID);
}

void RenderManager::LoadTexture()
{
	int width, height, n;
	//unsigned char *data = loadBitmapFile("myImage.bmp", &width, &height);

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
}

SDL_GLContext RenderManager::InitGL()
{
	SDL_GLContext openGL_Context = SDL_GL_CreateContext(mpWindow);

	glewExperimental = TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		// Problem: glewInit failed, something is seriously wrong.
		std::cout << "glewInit failed: " << glewGetErrorString(err) << std::endl;
		exit(1);
	}

	LoadShaders();

	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

	// Create a mesh

	// Generating 2 opengl buffer anmes/ids
	//0:Positions
	//1:Colors
	//2:Texture coordinates
	glGenBuffers(3, bufferIDs);

	int vertexNum = 4;
	int coordinatesPerPosition = 3;
	int coordinatesPerColor = 4;
	int coordinatesPerTextureCoordinates = 2;

	int positionStride = coordinatesPerPosition * sizeof(float);
	int colorStride = coordinatesPerColor * sizeof(float);
	int textureCoordinatesStride = coordinatesPerTextureCoordinates * sizeof(float);

	GLfloat *pPositions = new GLfloat[vertexNum*coordinatesPerPosition];
	GLfloat *pColors = new GLfloat[vertexNum*coordinatesPerColor];
	GLfloat *pTextureCoordinates = new GLfloat[vertexNum * coordinatesPerTextureCoordinates];

	// Vertex 1
	pPositions[0] = -0.5f; pPositions[1] = -0.5f; pPositions[2] = 0.0f;
	pColors[0] = 1.0f;  pColors[1] = 0.0f;	 pColors[2] = 0.0f; pColors[3] = 1.0f;
	pTextureCoordinates[0] = 0.0f;  pTextureCoordinates[1] = 0.25f;

	// Vertex 2
	pPositions[3] = 0.5f; pPositions[4] = -0.5f; pPositions[5] = 0.0f;
	pColors[4] = 0.0f;  pColors[5] = 1.0f;	 pColors[6] = 0.0f; pColors[7] = 1.0f;
	pTextureCoordinates[2] = 0.333f;  pTextureCoordinates[3] = 0.25f;

	// Vertex 3
	pPositions[6] = 0.5f; pPositions[7] = 0.5f; pPositions[8] = 0.0f;
	pColors[8] = 0.0f;  pColors[9] = 0.0f;	 pColors[10] = 1.0f; pColors[11] = 1.0f;
	pTextureCoordinates[4] = 0.333f;  pTextureCoordinates[5] = 0.0f;

	// Vertex 4
	pPositions[9] = -0.5f; pPositions[10] = 0.5f; pPositions[11] = 0.0f;
	pColors[12] = 0.0f;  pColors[13] = 0.0f;	 pColors[14] = 1.0f; pColors[15] = 1.0f;
	pTextureCoordinates[6] = 0.0f;  pTextureCoordinates[7] = 0.0f;

	// Copy data from RAM to buffers
	// Bind the created buffer 0:Position
	glBindBuffer(GL_ARRAY_BUFFER, bufferIDs[0]);
	// Copy the data
	glBufferData(GL_ARRAY_BUFFER, vertexNum*positionStride, pPositions, GL_STATIC_DRAW);
	// Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	/*
	glBindBuffer(GL_ARRAY_BUFFER, bufferIDs[1]);
	// Copy the data
	glBufferData(GL_ARRAY_BUFFER, vertexNum*colorStride, pColors, GL_STATIC_DRAW);
	// Unbind the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	*/
	// Bind the created buffer 2: Texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, bufferIDs[1]);
	// Copy the data
	glBufferData(GL_ARRAY_BUFFER, vertexNum*textureCoordinatesStride, pTextureCoordinates, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glFinish();
	delete[] pPositions;
	delete[] pColors;
	delete[] pTextureCoordinates;

	glGenBuffers(1, &texCoordBuffer);

	return openGL_Context;
}

void RenderManager::DrawSprite()
{
	float angle = 2.0f;
	int vertexNum = 4;

	glClear(GL_COLOR_BUFFER_BIT);

	int positionHandle = 0;
	glBindBuffer(GL_ARRAY_BUFFER, bufferIDs[0]);
	glEnableVertexAttribArray(positionHandle);
	glVertexAttribPointer(positionHandle,
		3,
		GL_FLOAT,
		false,
		0,
		0);

	/*
	int colorHandle = 1;
	glBindBuffer(GL_ARRAY_BUFFER, bufferIDs[1]);
	glEnableVertexAttribArray(colorHandle);
	glVertexAttribPointer(colorHandle,
		coordinatesPerColor,
		GL_FLOAT,
		false,
		0,
		0);
		*/

	//float transformMatrix[16];
	//memset(transformMatrix, 0, sizeof(transformMatrix));
	//angle += 2.0f;
	//float cosine = cosf(angle);
	//float sine = sinf(angle);
	/*
	transformMatrix[0] = transformMatrix[5] = transformMatrix[10] = transformMatrix[15] = 1.0f;
	transformMatrix[0] = cosine;
	transformMatrix[4] = -sine;
	transformMatrix[1] = sine;
	transformMatrix[5] = cosine;
	*/

	//const float RATE = 360.0f / 5.0f;

	const float RATE = 360.0f / 5.0f;
	const Hcoord AXIS(0, 0, 1, 0),
		CENTER(0.5, 0, 0, 0);

	Matrix M = scale(0.5f)
		*rotate(angle, AXIS)
		*translate(CENTER);

	int transformHandle = 2;
	glUniformMatrix4fv(transformHandle, 1, GL_FALSE, (float*)&M);

	int textureCoordinatesHandle = glGetAttribLocation(gProgramID, "in_TexCoords");;
	glEnableVertexAttribArray(textureCoordinatesHandle);
	glBindBuffer(GL_ARRAY_BUFFER, bufferIDs[2]);
	glVertexAttribPointer(textureCoordinatesHandle,
		2,
		GL_FLOAT,
		false,
		0,
		0);

	// Set the texture
	int texSamplerHandler = 4;
	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, gObj->mTextureID);
	glBindTexture(GL_TEXTURE_2D, 1);
	glUniform1i(texSamplerHandler, 0);

	glDrawArrays(GL_QUADS, 0, vertexNum);
	//glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
	glDisableVertexAttribArray(positionHandle);
	//glDisableVertexAttribArray(colorHandle);
	glDisableVertexAttribArray(textureCoordinatesHandle);
}

void RenderManager::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto obj : gameManagers->mpGameObjectManager->gameInstancesList) {
		if (obj == NULL) continue;
		Component_Sprite *pSt = (Component_Sprite*)obj->GetComponent(COMPONENT_SPRITE);
		if (pSt == NULL) continue;
		pSt->Render();
	}
}






