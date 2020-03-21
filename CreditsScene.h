#ifndef _CREDITS_SCENE_INCLUDE
#define _CREDITS_SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "CreditsNames.h"
#include "TileMap.h"
#include "Audio.h"

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

#pragma comment(lib, "irrKlang.lib") 

// CreditsScene contains all the entities of our game.
// It is responsible for updating and render them.

class CreditsScene
{

public:
	CreditsScene();
	~CreditsScene();

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
	std::vector<CreditsNames*> objects;
	int cont;
	Audio *audiomanager;
};

#endif // _CREDITS_SCENE_INCLUDE

