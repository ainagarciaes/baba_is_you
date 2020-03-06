#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "LevelController.h"
#include "Game.h"

void LevelController::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int lvl)
{
	std::cout << "init level controller" << std::endl;
	MapObject mo;
	mo.init(tileMapPos, shaderProgram, "bub");
	objects.push_back(mo);
}

void LevelController::update(int deltaTime)
{
	movePlayable(deltaTime);
	processQueries();
	updateNextScene();
}

void LevelController::render()
{
	// render objects
	for (int i = 0; i < objects.size(); ++i) {
		objects[i].render();
	}
	// render words
	for (int i = 0; i < words.size(); ++i) {
		words[i].render();
	}
}

void LevelController::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void LevelController::movePlayable(int deltaTime) {
	bool left = Game::instance().getSpecialKey(GLUT_KEY_LEFT);
	bool right = Game::instance().getSpecialKey(GLUT_KEY_RIGHT);
	bool up = Game::instance().getSpecialKey(GLUT_KEY_UP);
	bool down = Game::instance().getSpecialKey(GLUT_KEY_DOWN);

	string name;
	glm::ivec2 posPlayer;
	/*
		We have to iterate the map according to the direction the player wants to move, and then, for each playable element
		check if it can move to that direction taking into consideration:
			1. if there is a wall or the map ends
			2. if there is some blocking element (call to moveRecursive)
	*/
}

bool LevelController::moveRecursive(int deltaTime, string direction) {
	// recursively call moveRecursive if there is an object in the next position facing the direction
	// if there is a word and the call returns true, the word has to be moved
	return true;
}

void LevelController::processQueries() {
	//process queries in the map and change the required objects
}

int LevelController::getNextScene() {
	return nextScene;
}

void LevelController::updateNextScene() {
	//check if there is a win condition, if so, set the next scene to whatever it has to
}

bool LevelController::isPlayable(string name) {
	return playable[name];
}