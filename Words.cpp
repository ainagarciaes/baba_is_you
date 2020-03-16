#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Words.h"
#include "Game.h"


enum WordsAnims
{
	POS1,POS2,POS3,POS1C,POS2C,POS3C
};

Words::Words(const glm::vec2 &pos, string name, int wtype) {
	posWords = pos;
	wordName = name; 
	wordType = wtype;
}

void Words::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, string name)
{
	spritesheet.loadFromFile("../images/words/"+name+".png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.5, 0.33), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);
	
		sprite->setAnimationSpeed(POS1, 8);
		sprite->addKeyframe(POS1, glm::vec2(0.f, 0.f));
		
		sprite->setAnimationSpeed(POS2, 8);
		sprite->addKeyframe(POS2, glm::vec2(0.25f, 0.f));
		
		sprite->setAnimationSpeed(POS3, 8);
		sprite->addKeyframe(POS3, glm::vec2(0.f, 0.f));
		
		sprite->setAnimationSpeed(POS1C, 8);
		sprite->addKeyframe(POS1C, glm::vec2(0.25, 0.f));
				
		sprite->setAnimationSpeed(POS2C, 8);
		sprite->addKeyframe(POS2C, glm::vec2(0.25, 0.f));

		sprite->setAnimationSpeed(POS3C, 8);
		sprite->addKeyframe(POS3C, glm::vec2(0.25, 0.f));

		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posWords.x), float(tileMapDispl.y + posWords.y)));
}

void Words::update(int deltaTime, const glm::vec2 &pos, string dir)
{
	sprite->update(deltaTime);
	posWords = pos;
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
glm::vec2 Words::getPosition(){ return posWords;}

void Words::setPosition(const glm::vec2 &pos)
{
	posWords = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posWords.x), float(tileMapDispl.y + posWords.y)));
}

int Words::getWtype(){	
	return wordType;
}

string Words::getName(){ 
	return wordName;
}

/*
bool Words::checkFrase(){

	int newWT;
		//horizontal w1 noun at begin nVx
	if(wordType==1){
		newWT= lc.getTWordByPosition(glm::vec2(posWords.x+1,posWords.y));
		if(newWT==2)
			newWT= lc.getTWordByPosition(glm::vec2(posWords.x+2,posWords.y));
				if(newWT==3 or newWT==1)
					return true;
		//vertical w1 noun at begin nVx
		newWT= lc.getTWordByPosition(glm::vec2(posWords.x,posWords.y+1));
		if(newWT==2)
			newWT= lc.getTWordByPosition(glm::vec2(posWords.x,posWords.y+2));
				if(newWT==3 or newWT==1)
					return true;
		//horizontal noun at end xVn
		newWT= lc.getTWordByPosition(glm::vec2(posWords.x-1,posWords.y));
		if(newWT==2)
			newWT= lc.getTWordByPosition(glm::vec2(posWords.x-2,posWords.y));
				if(newWT==1)
					return true;
		//vertical w3 noun at end xVn
		newWT= lc.getTWordByPosition(glm::vec2(posWords.x,posWords.y-1));
		if(newWT==2)
			newWT= lc.getTWordByPosition(glm::vec2(posWords.x,posWords.y-2));
				if(newWT==1)
					return true;
		
	}
		//horizontal w2
	if(wordType==2){
		newWT= lc.getTWordByPosition(glm::vec2(posWords.x-1,posWords.y));
		if(newWT==1)
			newWT= lc.getTWordByPosition(glm::vec2(posWords.x+1,posWords.y));
				if(newWT==3 or newWT==1)
					return true;
		//vertical w2
		newWT= lc.getTWordByPosition(glm::vec2(posWords.x,posWords.y-1));
		if(newWT==1)
			newWT= lc.getTWordByPosition(glm::vec2(posWords.x,posWords.y+1));
				if(newWT==3 or newWT==1)
					return true;
		
	}
		//horizontal w3
	if(wordType==3){
		newWT= lc.getTWordByPosition(glm::vec2(posWords.x-1,posWords.y));
		if(newWT==2)
			newWT= lc.getTWordByPosition(glm::vec2(posWords.x-2,posWords.y));
				if(newWT==1)
					return true;
		//vertical w3
		newWT= lc.getTWordByPosition(glm::vec2(posWords.x,posWords.y-1));
		if(newWT==2)
			newWT= lc.getTWordByPosition(glm::vec2(posWords.x,posWords.y-2));
				if(newWT==1)
					return true;
		
	}
		else return false;
}
*/


