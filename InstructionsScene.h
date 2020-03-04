#ifndef _INSTRUCTIONS_SCENE_INCLUDE
#define _INSTRUCTIONS_SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480


// InstructionsScene contains all the entities of our game.
// It is responsible for updating and render them.

class InstructionsScene
{

public:
	InstructionsScene();
	~InstructionsScene();

	void init();
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
};


#endif // _INSTRUCTIONS_SCENE_INCLUDE

