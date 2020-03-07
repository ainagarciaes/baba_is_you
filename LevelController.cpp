#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "LevelController.h"
#include "Game.h"
#include <include/nlohmann/json.hpp>
#include<fstream>

// for convenience
using json = nlohmann::json;

void LevelController::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int lvl)
{
	std::cout << "init level controller" << std::endl;
	std::ifstream i("../levels/lvl_"+to_string(lvl)+"_setup.txt");
	json j;
	i >> j;

	// Read map words
	auto mapWords = j["mapWords"];
	for(auto i = 0; i < mapWords.size(); ++i) {
		string name = mapWords[i]["name"];
		int posy = mapWords[i]["posy"];
		int posx = mapWords[i]["posx"];

		//my code goes here
		MapObject *mo = new MapObject(glm::vec2(posx,posy), name);
		mo->init(tileMapPos, shaderProgram, name);
		obs_words_positions[posy%32][posx%32] = name;
		objects.push_back(mo);
	}

	// Read map objects
	auto mapObs = j["mapObjects"];
	for(auto i = 0; i < mapObs.size(); ++i) {
		string name = mapObs[i]["name"];
		int posy = mapObs[i]["posy"];
		int posx = mapObs[i]["posx"];

		//my code goes here
		MapObject *mo = new MapObject(glm::vec2(posx,posy), name);
		mo->init(tileMapPos, shaderProgram, name);
		obs_words_positions[posy%32][posx%32] = name;
		objects.push_back(mo);
	}

	// load map walls for collisions
	auto walls = j["walls"];
	for(auto i = 0; i < walls.size(); ++i) {
		int posy = walls[i]["posy"];
		int posx = walls[i]["posx"];
		obs_words_positions[posy][posx] = "wall";
	}

	moving = 0;
	// init properties
		// set animations for words	
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
		MapObject *ob = objects[i];
		ob->render();
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

	if (moving == 0) {
		//check collisions
		if (left) {
			moving = 1;
			for (int i = 0; i < objects.size(); ++i) { //TODO: ITERATE IN THE REQUIRED WAY
				MapObject *ob = objects[i];
				glm::ivec2 pos = ob->getPosition();
				pos.x -= 2;
				ob->update(deltaTime, pos, "L");
			}
		} else if (right) {
			moving = 2;
			for (int i = 0; i < objects.size(); ++i) {
				MapObject *ob = objects[i];
				glm::ivec2 pos = ob->getPosition();
				pos.x += 2;
				ob->update(deltaTime, pos, "R");
			}
		} else if (up) {
			moving = 3;
			for (int i = 0; i < objects.size(); ++i) {
				MapObject *ob = objects[i];
				glm::ivec2 pos = ob->getPosition();
				pos.y -= 2;
				ob->update(deltaTime, pos, "U");
			}
		} else if (down) {
			moving = 4;
			for (int i = 0; i < objects.size(); ++i) {
				MapObject *ob = objects[i];
				glm::ivec2 pos = ob->getPosition();
				pos.y += 2;
				ob->update(deltaTime, pos, "D");
			}
		} else {
			for (int i = 0; i < objects.size(); ++i) {
				MapObject *ob = objects[i];
				glm::ivec2 pos = ob->getPosition();
				ob->update(deltaTime, pos, "S");
			}
		}		
	} else {
		if (moving == 1) {
			for (int i = 0; i < objects.size(); ++i) {
				MapObject *ob = objects[i];
				glm::ivec2 pos = ob->getPosition();
				pos.x -= 2;
				ob->update(deltaTime, pos, "L");
				if (pos.x%32 == 0) moving = 0;
			}
		} else if (moving == 2) {
			for (int i = 0; i < objects.size(); ++i) {
				MapObject *ob = objects[i];
				glm::ivec2 pos = ob->getPosition();
				pos.x += 2;
				ob->update(deltaTime, pos, "R");
				if (pos.x%32 == 0) moving = 0;
			}
		} else if (moving == 3) {
			for (int i = 0; i < objects.size(); ++i) {
				MapObject *ob = objects[i];
				glm::ivec2 pos = ob->getPosition();
				pos.y -= 2;
				ob->update(deltaTime, pos, "U");
				if (pos.y%32 == 0) moving = 0;
			}
		} else if (moving == 4) {
			for (int i = 0; i < objects.size(); ++i) {
				MapObject *ob = objects[i];
				glm::ivec2 pos = ob->getPosition();
				pos.y += 2;
				ob->update(deltaTime, pos, "D");
				if (pos.y%32 == 0) moving = 0;
			}
		}
	}

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