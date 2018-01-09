#include "Component_Sprite.h"
#include "Component_Transform.h"
#include "GameManagers.h"
#define DEBUG 0

extern GameManagers *gameManagers;

Component_Sprite::Component_Sprite():Component(COMPONENT_SPRITE)
{
	mpSurface = NULL;
	mpOwner = NULL;
	mpWindowSurface = NULL;
	mImagePosX = 0;
	mImageRect.x = 0;
	mImageRect.y = 0;
	mImageRect.w = 32;
	mImageRect.h = 32;
}

Component_Sprite::~Component_Sprite()
{
}

void Component_Sprite::Update() {
	/*
	mImageRect.x = mImagePosX* mImageRect.w;
	mImageRect.y = mpOwner->mState * mImageRect.h;

	SDL_Rect destinationRect;

	Component_Transform *componentTransform = (Component_Transform*)mpOwner->GetComponent(COMPONENT_TRANSFORM);
	if (componentTransform == NULL) {
		printf("CANNOT UPDATE COMPONENT SPRITE--COMPONENT TRANSFORM IS NULL.\n");
		return;
	}

	destinationRect.x = componentTransform->mPosition.x;
	destinationRect.y = componentTransform->mPosition.y;
	SDL_BlitSurface(mpSurface, &mImageRect, mpWindowSurface, &destinationRect);
	*/
}

void Component_Sprite::Render()
{
	//if (mpOwner->mType != TYPE_MARIO)
	//	return;

	//angle++;
	int vertexNum = 4;

	int positionHandle = 0;
	glBindBuffer(GL_ARRAY_BUFFER, gameManagers->mpRenderManager->bufferIDs[0]);
	glEnableVertexAttribArray(positionHandle);
	glVertexAttribPointer(positionHandle,
		3,
		GL_FLOAT,
		false,
		0,
		0);


	Component_Transform *pTr = (Component_Transform*)mpOwner->GetComponent(COMPONENT_TRANSFORM);
	if (pTr == NULL) {
		printf("CANNOT UPDATE COMPONENT SPRITE--COMPONENT TRANSFORM IS NULL.\n");
		return;
	}

	const float RATE = 360.0f / 5.0f;
	const Hcoord AXIS(0, 0, 1, 0),
		//CENTER(pTr->mPosition.x / 50.0f, -pTr->mPosition.y / 50.0f, 0, 0);
		CENTER(pTr->mPosition.x, -pTr->mPosition.y, 0, 0);

	/*
	Matrix M = scale(0.1f)
		*rotate(angle, AXIS)
		*translate(CENTER);
		*/
	Matrix M;

	if (mpOwner->mType == TYPE_BRICK_H) {
		M = scale(720.0f, 40.0, 1.0)
			*rotate(angle, AXIS)
			*translate(CENTER);
	}
	else if (mpOwner->mType == TYPE_BRICK_V) {
		M = scale(40.0f, 720.0, 1.0)
			*rotate(angle, AXIS)
			*translate(CENTER);
	}
	else if (mpOwner->mType == TYPE_MARIO || mpOwner->mType == TYPE_BEN || mpOwner->mType == TYPE_JACK || mpOwner->mType == TYPE_SIMON) {
		M = scale(45.0)
			*rotate(angle, AXIS)
			*translate(CENTER);
	}
	else if (mpOwner->mType == TYPE_FIRE) {
		M = scale(50.0)
			*rotate(angle, AXIS)
			*translate(CENTER);
	}
	else if (mpOwner->mType == TYPE_BOMB) {
		M = scale(45.0)
			*rotate(angle, AXIS)
			*translate(CENTER);
	}
	else if (mpOwner->mType == TYPE_CONTROL_UI) {
		M = scale(720.0, 60.0, 1.0)
			*rotate(angle, AXIS)
			*translate(CENTER);
	}
	else if (mpOwner->mType == TYPE_WIN_UI) {
		M = scale(720.0, 60.0, 1.0)
			*rotate(angle, AXIS)
			*translate(CENTER);
	}
	else if (mpOwner->mType == TYPE_LOST_UI) {
		M = scale(720.0, 60.0, 1.0)
			*rotate(angle, AXIS)
			*translate(CENTER);
	}
	else {
		M = scale(50.0)
			*rotate(angle, AXIS)
			*translate(CENTER);

		/*
		M = translate(CENTER)
		*rotate(angle, AXIS)
		*scale(40.0f);
		*/
	}
	
	//Matrix P = translate(Hcoord(-1.0f, 1.0f, 0.0f, 0.0f)) * scale(2.0f / 600.0f, 2.0 / 600.0f, 0.0f) * translate(Hcoord(0.5f * sca.Vector2D_X(), -0.5f * sca.Vector2D_Y(), 0.0f, 0.0f));

	Matrix P;
	
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			P[i][j] = 0;

	P[0][0] = 2.0/800.0;
	P[1][1] = 2.0 / 800.0;
	P[2][2] = 1.0;
	P[3][3] = 1.0;
	P[0][3] = -1;
	P[1][3] = 1;
	

	/*
	P[0][0] = 2.0 / 800.0;
	P[0][3] = -1.0;
	P[1][1] = 2.0 / 800.0;
	P[1][3] = -1.0;
	P[2][2] = 1.0;
	P[3][3] = 1.0;
	*/
	Matrix V;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j)
				V[i][j] = 1.0;
			else
				V[i][j] = 0;
		}
	}

	/*
	float transformMatrix[16];
	memset(transformMatrix, 0, sizeof(transformMatrix));

	float cosine = cosf(angle);
	float sine = sinf(angle);

	transformMatrix[0] = transformMatrix[5] = transformMatrix[10] = transformMatrix[15] = 1.0f;
	transformMatrix[0] = cosine*0.1;
	transformMatrix[4] = -sine*0.1;
	transformMatrix[1] = sine*0.1;
	transformMatrix[5] = cosine*0.1;
	transformMatrix[12] = CENTER.x;
	transformMatrix[13] = CENTER.y;
	*/
	int transformHandle = 2;
	glUniformMatrix4fv(transformHandle, 1, GL_FALSE, (float*)&M);

	int uperspMatrixHandle = 5;
	int uviewMatrixHandle = 6;
	glUniformMatrix4fv(uperspMatrixHandle, 1, true, (float*)&P);
	glUniformMatrix4fv(uviewMatrixHandle, 1, true, (float*)&V);
	//glUniformMatrix4fv(transformHandle, 1, GL_FALSE, transformMatrix);

	GLfloat *pTextureCoordinates = new GLfloat[vertexNum * 2];

	if (mpOwner->mType == TYPE_MARIO || mpOwner->mType == TYPE_BEN || mpOwner->mType == TYPE_JACK || mpOwner->mType == TYPE_SIMON) {
		float x = mImagePosX* 1.0/3.0;
		float y = mpOwner->mState * 1.0/4.0;

		// Tex Coord 1
		pTextureCoordinates[0] = x;  pTextureCoordinates[1] = y+1.0/4.0;

		// Tex Coord 2
		pTextureCoordinates[2] = x + 1.0/3.0;  pTextureCoordinates[3] = y+1.0/4.0;

		// Tex Coord 3
		pTextureCoordinates[4] = x + 1.0/3.0;  pTextureCoordinates[5] = y;

		// Tex Coord 4
		pTextureCoordinates[6] = x;  pTextureCoordinates[7] = y;
	}
	else {
		// Tex Coord 1
		pTextureCoordinates[0] = 0; pTextureCoordinates[1] = 1.0;

		// Tex Coord 2
		pTextureCoordinates[2] = 1.0;  pTextureCoordinates[3] = 1.0;

		// Tex Coord 3
		pTextureCoordinates[4] = 1.0;  pTextureCoordinates[5] = 0;

		// Tex Coord 4
		pTextureCoordinates[6] = 0;  pTextureCoordinates[7] = 0;
	}


	//GLuint texBuffer;
	// Generate Buffer
	//glGenBuffers(1, &texBuffer);
	// Bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, gameManagers->mpRenderManager->texCoordBuffer);
	// Copy the data
	glBufferData(GL_ARRAY_BUFFER, vertexNum*2* sizeof(float), pTextureCoordinates, GL_STATIC_DRAW);
	// Unbind buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete[] pTextureCoordinates;

	int textureCoordinatesHandle = glGetAttribLocation(gameManagers->mpRenderManager->gProgramID, "in_TexCoords");;
	glEnableVertexAttribArray(textureCoordinatesHandle);
	glBindBuffer(GL_ARRAY_BUFFER, gameManagers->mpRenderManager->texCoordBuffer);
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
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glUniform1i(texSamplerHandler, 0);

	// Set the Mode
	int modeHandler = 10;
	glUniform1i(modeHandler, 1);

	glDrawArrays(GL_QUADS, 0, vertexNum);
	//glDeleteTextures(1, &texBuffer);
	//glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
	glDisableVertexAttribArray(positionHandle);
	//glDisableVertexAttribArray(colorHandle);
	glDisableVertexAttribArray(textureCoordinatesHandle);

	//glColor4f(0.0f, 1.0f, 1.0f, 0.5f);
	//glColor3f(1, 0, 0);// glEnableClientState(GL_COLOR_ARRAY);
	//glColor3f(1.0f, 1.0f, 1.0f); 

	if (DEBUG) {
		glUniform1i(modeHandler, 0);

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_STRIP);
		glVertex2f(-0.50f, -0.50f);
		glVertex2f(0.50f, -0.50f);
		glVertex2f(0.50f, 0.50f);
		glVertex2f(-0.50f, 0.50f);
		glVertex2f(-0.50f, -0.50f);
		glEnd();


		if (mpOwner->mType == TYPE_MARIO) {
			//glClearColor(0.0, 0.0, 0.0, 0.0);
			//glClear(GL_COLOR_BUFFER_BIT);
			glUniform1i(modeHandler, 0);
			glLineWidth(2.5);
			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_LINES);


			if (mpOwner->mState == Up) {
				glVertex2f(0.0, 0.0);
				glVertex2f(0, 1);
			}
			else if (mpOwner->mState == Down) {
				glVertex2f(0.0, 0.0);
				glVertex2f(0, -1);
			}
			else if (mpOwner->mState == Left) {
				glVertex2f(0.0, 0.0);
				glVertex2f(-1, 0);
			}
			else {
				glVertex2f(0.0, 0.0);
				glVertex2f(1, 0);
			}

			glEnd();
		}
	}
}

void Component_Sprite::SerializeOld(FILE ** fpp)
{
	char imageName[256];
	memset(imageName, 0, 256*sizeof(char));

	fscanf_s(*fpp, "%255s\n", imageName, sizeof(imageName));

	std::string fullPath = "..\\Resources\\";
	fullPath += imageName;

	mpSurface = gameManagers->mpResourceManager->LoadSurface((char*)fullPath.c_str());
}

void Component_Sprite::Serialize(FILE ** fpp)
{
	char imageName[256];
	memset(imageName, 0, 256 * sizeof(char));

	fscanf_s(*fpp, "%255s\n", imageName, sizeof(imageName));

	std::string fullPath = "..\\Resources\\";
	fullPath += imageName;

	mTextureID = gameManagers->mpResourceManager->LoadTexture((char*)fullPath.c_str());
}

