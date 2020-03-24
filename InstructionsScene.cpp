#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "InstructionsScene.h"
#include "Game.h"

#define SCREEN_X 0
#define SCREEN_Y 0

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

InstructionsScene::InstructionsScene()
{
	map = NULL;
}

InstructionsScene::~InstructionsScene()
{
	if(map != NULL)
		delete map;
}


void InstructionsScene::init(Audio *a)
{
	initShaders();
	map = TileMap::createTileMapMenu("../levels/instructions.txt", glm::vec2(0, 0), texProgram, true);
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	nextScene = -1;
	audiomanager = a;
	audiomanager->stopAllSounds();
	audiomanager->play(INSTRUCTIONS, true);
}

void InstructionsScene::update(int deltaTime)
{
	currentTime += deltaTime;
	if(Game::instance().getKey(8))
	{	
		nextScene = 0;
	} 
}

void InstructionsScene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
}

void InstructionsScene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "../shaders/texture.vert");

	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "../shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

int InstructionsScene::getNextScene() {
	return nextScene;
}