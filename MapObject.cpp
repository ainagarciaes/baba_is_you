#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "MapObject.h"
#include "Game.h"
#include "Texture.h"

long count;

enum MapObjectAnims
{
STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT,POS1,POS2,POS3
};

MapObject::MapObject(const glm::vec2 &pos, string name) {
posMapObject = pos;
objectName = name; 
}

void MapObject::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, string name)
{
	sp = shaderProgram;
	count==0;
	tileMapDispl = tileMapPos;
	initSprite(name);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posMapObject.x), float(tileMapDispl.y + posMapObject.y)));
}

void MapObject::initSprite(string name) {
	spritesheet.loadFromFile("../images/"+name+".png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f, 0.30), &spritesheet, &sp);
	sprite->setNumberAnimations(3);
	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->setAnimationSpeed(1, 8);
	sprite->addKeyframe(1, glm::vec2(0.f, 0.33f));
	sprite->setAnimationSpeed(2, 8);
	sprite->addKeyframe(2, glm::vec2(0.f, 0.66f));
	sprite->changeAnimation(0);
}

void MapObject::update(int deltaTime, const glm::vec2 &pos, string dir)
{
	sprite->update(deltaTime);
	posMapObject = pos;
	count++;

	if(sprite->animation() == 0 && count%8==0){
		sprite->changeAnimation(1); 
	}
	else if(sprite->animation() == 1 && count%8==0){
		sprite->changeAnimation(2); 
	}
	else if(sprite->animation() == 2 && count%8==0){
		sprite->changeAnimation(0);
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posMapObject.x), float(tileMapDispl.y + posMapObject.y)));
}

void MapObject::render()
{
	sprite->render();
}

void MapObject::setTileMap(TileMap *tileMap)
{
	tmap = tileMap;
}

void MapObject::setPosition(const glm::vec2 &pos)
{
	posMapObject = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posMapObject.x), float(tileMapDispl.y + posMapObject.y)));
}

string MapObject::getName(){
	return objectName;
}

glm::ivec2 MapObject::getPosition(){
	return posMapObject;
}

void MapObject::changeTo(string objectType){
	initSprite(objectType);
	objectName = objectType;
}
