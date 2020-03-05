#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "LevelController.h"
#include "Game.h"


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};


void LevelController::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int lvl)
{
	tileMapDispl = tileMapPos;
	// load lvl file
}

void LevelController::update(int deltaTime)
{
	processQueries();
	movePlayable(deltaTime);
	updateNextScene();
}


void LevelController::render()
{
	sprite->render();
}

void LevelController::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void LevelController::setPosition(const glm::vec2 &pos)
{
	posLevelController = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posLevelController.x), float(tileMapDispl.y + posLevelController.y)));
}

void LevelController::movePlayable(int deltaTime) {
	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		std::cout << "left" << std::endl;
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posLevelController.x -= 2;
		if(map->collisionMoveLeft(posLevelController, glm::ivec2(32, 32)))
		{
			posLevelController.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		std::cout << "right" << std::endl;
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posLevelController.x += 2;
		if(map->collisionMoveRight(posLevelController, glm::ivec2(32, 32)))
		{
			posLevelController.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	} 	
	else if(Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		std::cout << "up" << std::endl;
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posLevelController.y -= 2;
		if(map->collisionMoveUp(posLevelController, glm::ivec2(32, 32)))
		{
			posLevelController.y += 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		std::cout << "down" << std::endl;
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posLevelController.y += 2;
		if(map->collisionMoveDown(posLevelController, glm::ivec2(32, 32)))
		{
			posLevelController.y -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else
	{
		if(sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posLevelController.x), float(tileMapDispl.y + posLevelController.y)));
}

bool LevelController::moveRecursive(int deltaTime) {
	return true;
}

void LevelController::processQueries() {
	
}

int LevelController::getNextScene() {
	return nextScene;
}

void LevelController::updateNextScene() {

}