#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>
#include "MenuScene.h"
#include "Game.h"

#define SCREEN_X 0
#define SCREEN_Y 0

#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

MenuScene::MenuScene()
{
	std::cout<<"Creating a menu scene"<<std::endl;
	map = NULL;
}

MenuScene::~MenuScene()
{
	std::cout<<"Deleting a menu scene"<<std::endl;
	if(map != NULL)
		delete map;
}


void MenuScene::init()
{
	std::cout<<"INIT normal scene"<<std::endl;

	initShaders();
	map = TileMap::createTileMap("../levels/menu.txt", glm::vec2(32, 16), texProgram);
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	nextScene = -1;
}

void MenuScene::update(int deltaTime)
{
	currentTime += deltaTime;
	if(Game::instance().getSpecialKey(49))
	{
		nextScene = 1;
	}
}

void MenuScene::render()
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

void MenuScene::initShaders()
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

int MenuScene::getNextScene() {
	return nextScene;
}