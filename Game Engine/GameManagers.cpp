#include "GameManagers.h"

GameManagers::GameManagers()
{
	mpInputManager = new InputManager();
	mpFrameRateController = new FrameRateController(30);
	mpResourceManager = new ResourceManager();
	mpGameObjectManager = new GameObjectManager();
	mpPhysicsManager = new PhysicsManager();
	mpEventManager = new EventManager();
	mpRenderManager = new RenderManager();
	pwindowSurface = NULL;

	GameObjectMap = { { "Mario",TYPE_MARIO },
						{ "Ben",TYPE_BEN },
						{ "Jack",TYPE_JACK },
						{ "Simon",TYPE_SIMON }, 
						{"Bomb", TYPE_BOMB}, 
						{"Fire", TYPE_FIRE},
						{"Brick_H", TYPE_BRICK_H},
						{ "Brick_V", TYPE_BRICK_V },
						{ "Brick", TYPE_BRICK },
						{"Wood", TYPE_WOOD},
						{"PowerUpBomb", TYPE_POWERUP_BOMB},
						{"PowerUpFire", TYPE_POWERUP_FIRE},
						{"PowerUpSpeed", TYPE_POWERUP_SPEED},
						{"ControlUI", TYPE_CONTROL_UI},
						{"WinUI", TYPE_WIN_UI},
						{"LostUI", TYPE_LOST_UI},
						{"Door", TYPE_DOOR}
	};	
}

GameManagers::~GameManagers()
{
	delete mpInputManager;
	delete mpFrameRateController;
	delete mpResourceManager;
	delete mpGameObjectManager;
	delete mpPhysicsManager;
	delete mpEventManager;
}
