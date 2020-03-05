#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Words.h"
#include "Game.h"


enum WordsAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT
};

void Words::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile("../images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.25f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.5f));
		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posWords.x), float(tileMapDispl.y + posWords.y)));
	
}

void Words::update(int deltaTime)
{
	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		std::cout << "left" << std::endl;
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posWords.x -= 2;
		if(map->collisionMoveLeft(posWords, glm::ivec2(32, 32)))
		{
			posWords.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		std::cout << "right" << std::endl;
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posWords.x += 2;
		if(map->collisionMoveRight(posWords, glm::ivec2(32, 32)))
		{
			posWords.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	} 	
	else if(Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		std::cout << "up" << std::endl;
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posWords.y -= 2;
		if(map->collisionMoveUp(posWords, glm::ivec2(32, 32)))
		{
			posWords.y += 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		std::cout << "down" << std::endl;
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posWords.y += 2;
		if(map->collisionMoveDown(posWords, glm::ivec2(32, 32)))
		{
			posWords.y -= 2;
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
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posWords.x), float(tileMapDispl.y + posWords.y)));
}


void Words::render()
{
	sprite->render();
}

void Words::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Words::setPosition(const glm::vec2 &pos)
{
	posWords = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posWords.x), float(tileMapDispl.y + posWords.y)));
}




