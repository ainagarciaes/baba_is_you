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
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, STAND_UP, MOVE_UP, MOVE_DOWN, STAND_DOWN
};

MapObject::MapObject(const glm::vec2 &pos, string name) {
	posMapObject = pos;
	objectName = name; 
}

void MapObject::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, string name)
{
	sp = shaderProgram;
	count==0;
	destroy = false;
	tileMapDispl = tileMapPos;
	initSprite(name);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posMapObject.x), float(tileMapDispl.y + posMapObject.y)));
}

void MapObject::initSprite(string name) {
	spritesheet.loadFromFile("../images/objects/"+name+".png", TEXTURE_PIXEL_FORMAT_RGBA);
	// BABA
	if (name == "baba") {
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(.2f, 0.25), &spritesheet, &sp);
		sprite->setNumberAnimations(8);

		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.6f, 0.75f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.8f, 0.75f));

		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.6f, 0.0f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.8f, 0.0f));

		sprite->setAnimationSpeed(STAND_UP, 8);
		sprite->addKeyframe(STAND_UP, glm::vec2(0.6f, 0.25f));
		sprite->addKeyframe(STAND_UP, glm::vec2(0.8f, 0.25f));

		sprite->setAnimationSpeed(STAND_DOWN, 8);
		sprite->addKeyframe(STAND_DOWN, glm::vec2(0.6f, 0.5f));
		sprite->addKeyframe(STAND_DOWN, glm::vec2(0.8f, 0.5f));

		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.75f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.2f, 0.75f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.4f, 0.75f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.6f, 0.75f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.8f, 0.75f));

		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.2f, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.4f, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.6f, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.8f, 0.f));

		sprite->setAnimationSpeed(MOVE_UP, 8);
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.f, 0.25f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.2f, 0.25f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.4f, 0.25f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.6f, 0.25f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.8f, 0.25f));

		sprite->setAnimationSpeed(MOVE_DOWN, 8);
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.f, 0.5f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.2f, 0.5f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.4f, 0.5f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.6f, 0.5f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.8f, 0.5f));

		sprite->changeAnimation(STAND_RIGHT);
	} else {
		// Normal object
		cout << "CREATING " << name << endl;
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f, 0.30), &spritesheet, &sp);
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(0, glm::vec2(0.f, 0.33f));
		sprite->addKeyframe(0, glm::vec2(0.f, 0.66f));
		sprite->changeAnimation(0);
	}
}

void MapObject::update(int deltaTime, const glm::vec2 &pos, string dir)
{
	posMapObject = pos;
	// BABA
	if (objectName == "baba") {
		int anim = sprite->animation();
		if (dir == "U" && anim != MOVE_UP){ //only if it was not that one first CHECK!
			sprite->changeAnimation(MOVE_UP);
		} else if (dir == "D" && anim != MOVE_DOWN) {
			sprite->changeAnimation(MOVE_DOWN);
		} else if (dir == "L" && anim != MOVE_LEFT) {
			sprite->changeAnimation(MOVE_LEFT);
		} else if (dir == "R" && anim != MOVE_RIGHT) {
			sprite->changeAnimation(MOVE_RIGHT);
		} else if (dir == "S") {
			int animation = sprite->animation();
			if (animation == MOVE_UP) sprite->changeAnimation(STAND_UP);
			else if (animation == MOVE_DOWN) sprite->changeAnimation(STAND_DOWN);
			else if (animation == MOVE_LEFT) sprite->changeAnimation(STAND_LEFT);
			else if (animation == MOVE_RIGHT) sprite->changeAnimation(STAND_RIGHT);
		}
	}

	sprite->update(deltaTime);
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

void MapObject::destroyObj() {
	destroy = true;
}

bool MapObject::getDestroy() {
	return destroy;
}

string MapObject::getMovement() {
	int anim = sprite->animation();
	string dir;
	switch(anim) {
		case MOVE_DOWN:
		dir = "D";
		break;
		case MOVE_LEFT:
		dir = "L";
		break;
		case MOVE_RIGHT:
		dir = "R";
		break;
		case MOVE_UP:
		dir = "U";
		break;
		default:
		dir = " ";
	}
	return dir;
}
