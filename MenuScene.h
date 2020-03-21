#ifndef _MENU_SCENE_INCLUDE
#define _MENU_SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Audio.h"
#pragma comment(lib, "irrKlang.lib") 

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480


// MenuScene contains all the entities of our game.
// It is responsible for updating and render them.

class MenuScene
{

public:
	MenuScene();
	~MenuScene();

	void init(Audio *a);
	void update(int deltaTime);
	void render();
	int getNextScene();
private:
	void initShaders();

private:
	TileMap *map;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int nextScene;
	Audio *audiomanager;

};


#endif // _MENU_SCENE_INCLUDE

