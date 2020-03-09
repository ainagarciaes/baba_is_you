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

	for (int k = 0; k < 15; k++) {
		for (int w = 0; w < 20; w++) {
			obs_words_positions[k][w] = "empty";
		}
	}

	std::ifstream i("../levels/lvl_"+to_string(lvl)+"_setup.txt");
	json j;
	i >> j;

	// Read map words
	auto mapWords = j["mapWords"];
	for(auto i = 0; i < mapWords.size(); ++i) {
		string name = mapWords[i]["name"];
		int posy = mapWords[i]["posy"];
		int posx = mapWords[i]["posx"];
		string id = mapWords[i]["idw"];
		int wtype = mapWords[i]["wtype"];

		//my code goes here
		Words *mo = new Words(glm::vec2(posx,posy), name, wtype);
		mo->init(tileMapPos, shaderProgram, name);
		obs_words_positions[posy%32][posx%32] = name;
		words[id]=mo;
	}

	// Read map objects
	auto mapObs = j["mapObjects"];
	for(auto i = 0; i < mapObs.size(); ++i) {
		string name = mapObs[i]["name"];
		int posy = mapObs[i]["posy"];
		int posx = mapObs[i]["posx"];
		string id = mapObs[i]["ido"];

		//my code goes here
		MapObject *mo = new MapObject(glm::vec2(posx,posy), name);
		mo->init(tileMapPos, shaderProgram, name);
		cout << posy%32 << posx%32 << id << endl;
		obs_words_positions[posy/32][posx/32] = id;
		objects[id] = mo;
		playable[name] = false;
	}
	playable["bub"] = true;

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
	std::map<std::string, MapObject*>::iterator it = objects.begin();
 	while (it != objects.end())
	{
		MapObject *o = it->second;
		o->render();
		it++;
	}

	// render objects
	std::map<std::string, Words*>::iterator it2 = words.begin();
 	while (it2 != words.end())
	{
		Words *o = it2->second;
		o->render();
		it2++;
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
		if (left) { // TODO: ADD PUSHABLE OBJECTS
			moving = 1; 
			for (int i = 1; i < 19; i++) {
				for (int j = 1; j < 14; j++) { // check map state
					string id = obs_words_positions[j][i];
					// we check that there is not another object at the left of the player and that this object exists
					if (moveRecursive(deltaTime, "L", i, j) && objects.find(id) != objects.end()) {
						MapObject *ob = objects[id];
						glm::ivec2 pos = ob->getPosition();
						if (playable[ob->getName()]) { // If it is playable and it does not collide, it can move
							pos.x -= 2;
							ob->update(deltaTime, pos, "L");
							obs_words_positions[j][i-1] = obs_words_positions[j][i];
							obs_words_positions[j][i] = "empty";
						}
					}
				}
			}
			movCont = 14;
		} else if (right) {
			moving = 2;
			for (int i = 0; i < objects.size(); ++i) {
				MapObject *ob = objects[to_string(i)];
				glm::ivec2 pos = ob->getPosition();
				pos.x += 2;
				ob->update(deltaTime, pos, "R");
			}
			movCont = 14;
		} else if (up) {
			moving = 3;
			for (int i = 0; i < objects.size(); ++i) {
				MapObject *ob = objects[to_string(i+1)];
				glm::ivec2 pos = ob->getPosition();
				pos.y -= 2;
				ob->update(deltaTime, pos, "U");
			}
			movCont = 14;
		} else if (down) {
			moving = 4;
			for (int i = 0; i < objects.size(); ++i) {
				MapObject *ob = objects[to_string(i+1)];
				glm::ivec2 pos = ob->getPosition();
				pos.y += 2;
				ob->update(deltaTime, pos, "D");
			}
			movCont = 14;
		} else {
			for (int i = 0; i < objects.size(); ++i) {
				MapObject *ob = objects[to_string(i+1)];
				glm::ivec2 pos = ob->getPosition();
				ob->update(deltaTime, pos, "S");
			}
		}		
	} else {
		if (moving == 1) {
			for (int i = 0; i < objects.size(); ++i) {
				MapObject *ob = objects[to_string(i+1)];
				glm::ivec2 pos = ob->getPosition();
				if (pos.x % 32 != 0) {
					pos.x -= 2;
					ob->update(deltaTime, pos, "L");
				}
			}
		} else if (moving == 2) {
			for (int i = 0; i < objects.size(); ++i) {
				MapObject *ob = objects[to_string(i+1)];
				glm::ivec2 pos = ob->getPosition();
				pos.x += 2;
				ob->update(deltaTime, pos, "R");
			}
		} else if (moving == 3) {
			for (int i = 0; i < objects.size(); ++i) {
				MapObject *ob = objects[to_string(i+1)];
				glm::ivec2 pos = ob->getPosition();
				pos.y -= 2;
				ob->update(deltaTime, pos, "U");
			}
		} else if (moving == 4) {
			for (int i = 0; i < objects.size(); ++i) {
				MapObject *ob = objects[to_string(i+1)];
				glm::ivec2 pos = ob->getPosition();
				pos.y += 2;
				ob->update(deltaTime, pos, "D");
			}
		}
		if (movCont == 0) moving = 0;
		movCont -= 1;
	}

	/*
		We have to iterate the map according to the direction the player wants to move, and then, for each playable element
		check if it can move to that direction taking into consideration:
			1. if there is a wall or the map ends
			2. if there is some blocking element (call to moveRecursive)
	*/
}

bool LevelController::moveRecursive(int deltaTime, string direction, int x, int y) {
	if (x == 0 || y == 0) {
		return false;
	}


	if (obs_words_positions[y][x] == "empty") {
		return true;
	} else if (obs_words_positions[y][x] == "wall") {
		return false;
	} else {
		// other cases, check if it is an object and it is pushable, etc...
	}
	
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