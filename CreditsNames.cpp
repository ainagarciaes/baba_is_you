#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "CreditsNames.h"
#include "Game.h"
#include "Texture.h"

CreditsNames::CreditsNames(const glm::vec2 &pos) {
	posCreditsNames = pos;
}

void CreditsNames::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, float x, float y)
{
	bool ok = spritesheet.loadFromFile("../images/names_credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.1666, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(x, y));
	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(tileMapPos.x, tileMapPos.y));
}

void CreditsNames::update(int deltaTime, const glm::vec2 &pos, string dir)
{
	sprite->update(deltaTime);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posCreditsNames.x), float(tileMapDispl.y + posCreditsNames.y)));
}


void CreditsNames::render()
{
	sprite->render();
}

void CreditsNames::setTileMap(TileMap *tileMap)
{
	tmap = tileMap;
}

void CreditsNames::setPosition(const glm::vec2 &pos)
{
	posCreditsNames = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posCreditsNames.x), float(tileMapDispl.y + posCreditsNames.y)));
}

glm::ivec2 CreditsNames::getPosition(){
	return posCreditsNames;
}