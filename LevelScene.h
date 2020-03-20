#ifndef _LEVEL_SCENE_INCLUDE
#define _LEVEL_SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "LevelController.h"
#include "Audio.h"

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

#pragma comment(lib, "irrKlang.lib") 

// LevelScene contains all the entities of our game.
// It is responsible for updating and render them.

class LevelScene
{
public:
	LevelScene();
	~LevelScene();

	void init(int lvl, Audio *a);
	void update(int deltaTime);
	void render();
	int getNextScene();
	LevelController getLevelC();

private:
	void initShaders();

private:
	TileMap *map;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int nextScene;
	int mylevel;
	LevelController *levelController;
	Audio *audiomanager;
};


#endif // _LEVEL_SCENE_INCLUDE

