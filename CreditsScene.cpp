#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>
#include "CreditsScene.h"
#include "CreditsNames.h"
#include "Game.h"

#define SCREEN_X 0
#define SCREEN_Y 0

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

CreditsScene::CreditsScene()
{
	map = NULL;
}

CreditsScene::~CreditsScene()
{ 
	if(map != NULL)
		delete map;
}

void CreditsScene::init(Audio *a)
{
	initShaders();
	cont = 0;
	objects = {};
	map = TileMap::createTileMapMenu("../levels/credits.txt", glm::vec2(0, 0), texProgram, true);
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	nextScene = -1;

	for (int i = 0; i < 6; i++){
		CreditsNames *mo = new CreditsNames(glm::ivec2(i*32+7*32, 480-64));
		mo->init(glm::ivec2(i*32+7*32, 480-64), texProgram, i/float(6),0);
		objects.push_back(mo);
	}
	
	audiomanager = a;
	audiomanager->stopAllSounds();
	audiomanager->play(CREDITS, true);
}

void CreditsScene::update(int deltaTime)
{
	currentTime += deltaTime;
	if(Game::instance().getKey(8))
	{	
		nextScene = 0;
	}
	
	for (int i = 0; i < objects.size(); i++) {
		glm::vec2 pos = objects[i]->getPosition();
		pos.y -= 2;
		objects[i]->setPosition(pos);
	}
	cont++;
	if (cont == 300) {
		nextScene = 0;
	}
}

void CreditsScene::render()
{
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->render();
	}
}

void CreditsScene::initShaders()
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

int CreditsScene::getNextScene() {
	return nextScene;
}
