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

void CreditsNames::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int x, int y)
{
	bool ok = spritesheet.loadFromFile("../images/credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
	std::cout<<ok<<std::endl;
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(x, y), &spritesheet, &shaderProgram);
}

void CreditsNames::update(int deltaTime, const glm::vec2 &pos, string dir)
{
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