																				IS IMPLEMENTED				NOTE
- Game must be in C++. 		  													YES
- Game must run on DigiPen’s lab machines.										YES

* Debug Drawing																								To enable debug drawing, set the DEBUG variable to 1 in Component_Sprite.cpp, line 4
- Basic Debug Drawing – Simple Lines and bound volumes. 						YES
- Advanced Debug Drawing – Text, duration, or other features +2					NO

* Object Architecture
- Component Based or Other Advanced Design 										YES
- Game Object Ids, Garbage Collection or some form of object management +2		YES

* Communication
- Basic Events. 																YES
- Subscription Model +4															YES

* Data Driven Design														  		
- Basic Text Serialization. (Missing: -20)										YES
- Creation of objects from data files. +2										YES
- More advanced serialization or multiple formats. +2							NO
- Level Files +2																YES
- Archetypes +2																	YES		
- Level Editor +4																NO

* Frame rate Controller
- Game’s frame rate should be controlled (Not implicitly through V-Sync) 
20)																				YES

* Input
- Input Manager providing keyboard and mouse key and button “IsPressed”,
“IsTriggered” and “IsReleased” detection. (Missing: -30 points)					YES

* Graphics
- Hardware accelerated sprite rendering using shaders (textured quads/meshes in
OpenGL or DirectX). (Missing: -20)												YES
- Basic Sprite transformation (Translation, Rotation, and Scale). 				YES
- Sprite Animations +2															YES
- Sprite Z Sorting + 2															NO
- Sprite Batching +2															NO
- Other advanced graphics features (Any +2, Max +6)								NO

* Physics
- Basic collision detection between circles/AABB. (Missing: -20)				YES
- Basic Collision response (bouncing etc…). (Missing: -10)						YES                     Player ajusts the position when he collides with objects 
- Impulse base collision response +2											NO
- Collision between different bodies type (circle, quad) +2						NO
- Advanced physics (rotations, constraint based, stacking, etc…) up to +6		NO

* Game Requirements
- Human player control of a ship, avatar, or character. (Missing: -20)			YES
- Game runs at 30 fps most of the time. (Missing: -10)							YES
- At least 2 different types of enemies with different behaviors. 				YES 					One type of enemy has UpDown Componnet, the other type head to random direction(they are not trapped)
- Additional enemy behavior +2 (Max 6)											NO

- Player has 2 different types of weapons or power ups. (Missing: -10)			YES
- Addition weapon type +2 (Max 6)												YES 					Player has 3 types of powerups, Speed, ability to place more bombs and bomb power
- Collision between projectiles, player, and enemies. (Missing -20)				YES

- In-game controls screen (Missing -20)											YES
- Menus +2																		NO
- Game must have a win / lose condition. (Missing -20)							YES
- Game is fun for a few minutes (or funny, interesting, surprising) +4			YES